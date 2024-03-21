/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:51 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/21 16:21:33 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line_len(char *buffer)
{
	int	len;

	len = 0;
	while (len < BUFFER_SIZE)
	{
		if (!buffer[len])
			return (len);
		if (buffer[len] == '\n')
			return (len + 1);
		len++;
	}
	return (-1);
}

char	*get_next_line_rec(int fd, char *buffer, char *result)
{
	int	len;

	if (!buffer[0])
		read(fd, buffer, BUFFER_SIZE);
	len = get_next_line_len(buffer);
	if (!len)
		return (result);

	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*result;

	return (NULL);
	result = NULL;
	result = get_next_line_rec(fd, buffer, result);
	return (result);
}
