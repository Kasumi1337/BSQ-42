/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:14:53 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/26 17:07:10 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reader.h"
#include "../includes/boolean.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

inline static ssize_t	file_get_size(const char *file)
{
	const int	fd = open(file, O_RDONLY);
	static char	buff[BUFF_SIZE];
	ssize_t		length;
	ssize_t		readed;

	if (fd == -1)
		return (-1);
	length = 0;
	while (TRUE)
	{
		readed = read(fd, buff, BUFF_SIZE);
		if (readed < 1)
			break ;
		length += readed;
	}
	if (close(fd) == -1 || readed == -1)
		return (-1);
	return (length);
}

char	*file_read(const char *file)
{
	const ssize_t	length = file_get_size(file);
	int				fd;
	char			*content;

	if (length == -1)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = malloc(length + 1);
	if (content == NULL)
		return (close(fd), NULL);
	if (read(fd, content, length + 1) != length)
		return (free(content), close(fd), NULL);
	if (close(fd) == -1)
		return (free(content), NULL);
	content[length] = 0;
	return (content);
}
