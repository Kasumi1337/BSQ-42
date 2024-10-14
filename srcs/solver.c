/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:10:28 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 16:19:52 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

inline static unsigned int	min(unsigned int a, unsigned int b, unsigned int c)
{
	unsigned int	m;

	m = a;
	if (m > b)
		m = b;
	if (m > c)
		m = c;
	return (m);
}

inline static unsigned int	calculate_index(const t_solver *solver, size_t i,
	size_t j)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	a = solver->dp[(i - 1) * solver->line_size + j];
	b = solver->dp[i * solver->line_size + (j - 1)];
	c = solver->dp[(i - 1) * solver->line_size + (j - 1)];
	return (min(a, b, c) + 1);
}

t_bool	solver_init(t_solver *solver, const t_map *map)
{
	solver->line_size = map->line_size + 1;
	solver->dp = malloc(map->line_count * \
	solver->line_size * sizeof(unsigned int));
	if (!solver->dp)
		return (FALSE);
	solver->max_size = 0;
	solver->max_row = 0;
	solver->max_col = 0;
	return (TRUE);
}

void	map_fill(t_map *map, const t_solver *solver)
{
	size_t	i;
	size_t	j;

	i = solver->max_row + 1 - solver->max_size;
	while (i <= solver->max_row)
	{
		j = solver->max_col + 1 - solver->max_size;
		while (j <= solver->max_col)
			map->matrix[i * solver->line_size + j++] = map->full_char;
		i++;
	}
}

void	map_solve(t_map *map, t_solver *solver)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = -1;
	while (++i < map->line_count)
	{
		j = -1;
		while (++j < map->line_size)
		{
			index = i * solver->line_size + j;
			if (map->matrix[index] == map->obstacle_char)
				solver->dp[index] = 0;
			else if (i == 0 || j == 0)
				solver->dp[index] = 1;
			else
				solver->dp[index] = calculate_index(solver, i, j);
			if (solver->dp[index] <= solver->max_size)
				continue ;
			solver->max_size = solver->dp[index];
			solver->max_row = i;
			solver->max_col = j;
		}
	}
}
