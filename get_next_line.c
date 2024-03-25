/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:51 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/25 13:01:16 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_add_buffer(char *old_str, char *buf, int buf_len)
{
	char	*result;
	int		len;
	int		i;

	if (!old_str)
		len = buf_len;
	else
		len = ft_strlen(old_str) + buf_len;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	i = 0;
	while (old_str && old_str[i])
	{
		result[i] = old_str[i];
		i++;
	}
	while (i < len)
		result[i++] = *(buf++);
	free(old_str);
	return (result);
}

void	get_next_line_rec(int fd, char *buf, char **result, int pos)
{
	int		len;
	int		i;
	int		readlen;

	readlen = 0;
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
	*result = str_add_buffer(*result, buf + pos, len);
	if (pos + len == BUFFER_SIZE && buf[BUFFER_SIZE - 1] == '\n')
	{
		while (pos < BUFFER_SIZE)
			buf[pos++] = '\0';
		return ;
	}
	len = pos + len;
	while (pos < len)
		buf[pos++] = '\0';
	if (pos == BUFFER_SIZE && *result)
	{
		readlen = read(fd, buf, BUFFER_SIZE);
		if (readlen < 0)
		{
			i = 0;
			while (i < BUFFER_SIZE)
				buf[i++] = '\0';
			free(*result);
			*result = NULL;
			return ;
		}
		if (readlen > 0)
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
		{
			i = 0;
			while (i < BUFFER_SIZE)
				buf[i++] = '\0';
		}
		else if (readlen > 0)
			return (get_next_line(fd));
		return (NULL);
	}
	get_next_line_rec(fd, buf, &result, i);
	return (result);
}
