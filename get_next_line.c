/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:51 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/25 15:26:21 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_next_line_len(char *buf, int pos)
{
	int	len;

	len = 0;
	while (pos + len < BUFFER_SIZE)
	{
		if (buf[pos + len] == '\n')
		{
			len++;
			break ;
		}
		if (!buf[pos + len])
			break ;
		len++;
	}
	return (len);
}

static void	get_next_line_rec(int fd, char *buf, char **result, int pos)
{
	int	len;
	int	i;
	int	readlen;

	len = get_next_line_len(buf, pos);
	*result = str_add_buffer(*result, buf + pos, len);
	if (pos + len == BUFFER_SIZE && buf[BUFFER_SIZE - 1] == '\n')
		return (clear_buffer(buf, pos));
	i = 0;
	while (i < len)
		buf[pos + i++] = '\0';
	if (pos + len == BUFFER_SIZE && *result)
	{
		readlen = read(fd, buf, BUFFER_SIZE);
		if (readlen < 0)
		{
			clear_buffer(buf, 0);
			free(*result);
			*result = NULL;
		}
		else if (readlen > 0)
			get_next_line_rec(fd, buf, result, 0);
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	int			i;
	char		*result;
	int			readlen;

	i = 0;
	readlen = 0;
	result = NULL;
	while (i < BUFFER_SIZE && !buf[i])
		i++;
	if (i == BUFFER_SIZE)
	{
		readlen = read(fd, buf, BUFFER_SIZE);
		if (readlen < 0)
			clear_buffer(buf, 0);
		else if (readlen > 0)
			return (get_next_line(fd));
		return (NULL);
	}
	get_next_line_rec(fd, buf, &result, i);
	return (result);
}
