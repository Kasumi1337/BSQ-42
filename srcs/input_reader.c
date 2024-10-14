/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:12:34 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/25 15:31:05 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reader.h"
#include "../includes/boolean.h"
#include <stdlib.h>
#include <unistd.h>

inline static t_readerpart	*part_create(const char *content, size_t size)
{
	t_readerpart	*part;
	char			*ptr;

	part = malloc(sizeof(t_readerpart));
	if (part == NULL)
		return (NULL);
	ptr = malloc(size);
	if (ptr == NULL)
		return (free(part), NULL);
	part->content = ptr;
	part->size = size;
	part->next = NULL;
	while (size--)
		*ptr++ = *content++;
	return (part);
}

static void	reader_free(t_reader *reader)
{
	t_readerpart	*part;
	t_readerpart	*tmp;

	part = reader->start;
	while (part)
	{
		tmp = part->next;
		free(part->content);
		free(part);
		part = tmp;
	}
}

inline static void	reader_add(t_reader *reader, t_readerpart *part)
{
	if (reader->end)
		reader->end->next = part;
	else
		reader->start = part;
	reader->end = part;
	reader->size += part->size;
}

static void	reader_cpy(t_reader *reader, char *content)
{
	t_readerpart	*part;
	t_readerpart	*tmp;
	const char		*ptr;

	part = reader->start;
	while (part)
	{
		ptr = part->content;
		while (part->size--)
			*content++ = *ptr++;
		tmp = part->next;
		free(part->content);
		free(part);
		part = tmp;
	}
}

char	*input_read(void)
{
	char			buff[BUFF_SIZE];
	t_reader		reader;
	t_readerpart	*part;
	char			*content;
	ssize_t			readed;

	reader = (t_reader){NULL, NULL, 0};
	while (TRUE)
	{
		readed = read(STDIN_FILENO, buff, BUFF_SIZE);
		if (readed == -1)
			return (reader_free(&reader), NULL);
		if (readed == 0)
			break ;
		part = part_create(buff, (size_t)readed);
		if (part == NULL)
			return (reader_free(&reader), NULL);
		reader_add(&reader, part);
	}
	content = malloc(reader.size + 1);
	if (content == NULL)
		return (reader_free(&reader), NULL);
	reader_cpy(&reader, content);
	content[reader.size] = 0;
	return (content);
}
