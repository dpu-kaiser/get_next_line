/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:51 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/22 16:51:40 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*str_add_buffer(char *old_str, char *buf, int pos, int buf_len)
{
	char	*result;
	int		len;
	int		i;

	if (!old_str)
		len = buf_len;
	else
		len = ft_strlen(old_str) + buf_len;
	result = malloc(sizeof(char) * len);
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
		result[i++] = buf[pos++];
	return (result);
}

void	get_next_line_rec(int fd, char *buf, char **ptr_result, int pos)
{
	int		len;
	int		i;
	char	*old_res;
	char	*result;
	int		readlen;

	result = *ptr_result;
	readlen = 0;
	len = 0;
	while (pos + len < BUFFER_SIZE)
	{
		if (buf[pos + len] == '\n')
		{
			len++;
			break;
		}
		if (!buf[pos + len])
			break ;
		len++;
	}
	old_res = result;
	result = str_add_buffer(old_res, buf, pos, len);
	*ptr_result = result;
	free(old_res);
	if (!result)
		return ;
	i = 0;
	while (i < len)
		buf[pos + i++] = '\0';
	if (pos + len == BUFFER_SIZE)
	{
		readlen = read(fd, buf, BUFFER_SIZE);
		if (readlen > 0)
			get_next_line_rec(fd, buf, &result, 0);
	}
	*ptr_result = result;
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
		if (readlen > 0)
			return (get_next_line(fd));
		return (NULL);
	}
	get_next_line_rec(fd, buf, &result, i);
	return (result);
}
