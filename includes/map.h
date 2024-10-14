/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:07:51 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 15:14:43 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H

# define MAP_H

# include "solver.h"
# include <stddef.h>

typedef struct s_map
{
	size_t	line_count;
	size_t	line_size;
	char	void_char;
	char	obstacle_char;
	char	full_char;
	char	*matrix;
}	t_map;

t_bool	map_parse(char *content, t_map *map);

void	map_fill(t_map *map, const t_solver *solver);

void	map_solve(t_map *map, t_solver *solver);

#endif