/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:07:51 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 15:14:37 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H

# define SOLVER_H

# include "boolean.h"
# include <stddef.h>

typedef struct s_map	t_map;

typedef struct s_solver
{
	unsigned int	*dp;
	size_t			line_size;
	size_t			max_size;
	size_t			max_row;
	size_t			max_col;
}	t_solver;

t_bool	solver_init(t_solver *solver, const t_map *map);

#endif
