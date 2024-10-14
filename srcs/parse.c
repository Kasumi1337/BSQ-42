/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:49:41 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 17:57:18 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdio.h>

inline static char	*str_chr(char *str, char c, size_t *size)
{
	char	*ptr;

	ptr = str;
	while (*ptr && *ptr != c)
		ptr++;
	*size = ptr - str;
	if (*ptr == 0)
		return (NULL);
	return (ptr);
}

static int	atoi_check(const char *str, size_t size)
{
	int		nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (i < size)
	{
		if (i == 9)
		{
			if (nb > 214748364)
				return (0);
			else if (nb == 214748364 && str[i] > '7')
				return (0);
		}
		if (str[i] < '0' || str[i] > '9')
			return (0);
		nb = nb * 10 + (str[i++] - '0');
	}
	return (nb);
}

inline static t_bool	is_printable(char c)
{
	return (c >= ' ' && c < 127);
}

static t_bool	map_parse_first_line(char *content, t_map *map)
{
	size_t	line_size;
	char	*end;

	end = str_chr(content, '\n', &line_size);
	if (end == NULL || line_size < 4 || line_size > 13)
		return (FALSE);
	map->line_count = atoi_check(content, line_size - 3);
	if (map->line_count == 0)
		return (FALSE);
	map->void_char = content[line_size - 3];
	map->obstacle_char = content[line_size - 2];
	map->full_char = content[line_size - 1];
	map->matrix = end + 1;
	return (is_printable(map->void_char) && is_printable(map->obstacle_char)
		&& is_printable(map->full_char) && map->void_char != map->obstacle_char
		&& map->void_char != map->full_char
		&& map->obstacle_char != map->full_char);
}

t_bool	map_parse(char *content, t_map *map)
{
	const char	*ptr;
	size_t		line_size;
	size_t		line_count;

	if (!map_parse_first_line(content, map))
		return (FALSE);
	content = str_chr(map->matrix, '\n', &line_size);
	if (content == NULL || line_size == 0)
		return (FALSE);
	map->line_size = line_size;
	line_count = 0;
	while (content && ++line_count)
	{
		if (line_size != map->line_size)
			return (FALSE);
		ptr = content - line_size;
		while (*ptr != '\n')
		{
			if (*ptr != map->void_char && *ptr != map->obstacle_char)
				return (FALSE);
			ptr++;
		}
		content = str_chr(content + 1, '\n', &line_size);
	}
	return (line_size == 0 && line_count == map->line_count);
}
