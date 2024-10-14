/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeil <tbeil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:19:32 by tbeil             #+#    #+#             */
/*   Updated: 2024/09/23 19:19:36 by tbeil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H

# define READER_H

# include <stddef.h>

# define BUFF_SIZE 16384

typedef struct s_readerpart
{
	char				*content;
	size_t				size;
	struct s_readerpart	*next;
}	t_readerpart;

typedef struct s_reader
{
	t_readerpart	*start;
	t_readerpart	*end;
	size_t			size;
}	t_reader;

char	*file_read(const char *file);

char	*input_read(void);

#endif
