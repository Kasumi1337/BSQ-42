/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:58:40 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 15:31:15 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reader.h"
#include "../includes/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

inline static void	show_error(void)
{
	write(STDERR_FILENO, "map error\n", 10);
}

inline static void	show_map(const t_map *map)
{
	write(STDOUT_FILENO, map->matrix, map->line_count * (map->line_size + 1));
}

static void	process_content(char *content)
{
	t_map		map;
	t_solver	solver;

	if (content && map_parse(content, &map) && solver_init(&solver, &map))
	{
		map_solve(&map, &solver);
		map_fill(&map, &solver);
		show_map(&map);
		free(solver.dp);
	}
	else
		show_error();
	free(content);
}

int	main(int argc, const char *argv[])
	{
	if (argc == 1)
		process_content(input_read());
	else
	{
		while (--argc)
		{
			process_content(file_read(*++argv));
			if (argc != 1)
				write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (0);
}
