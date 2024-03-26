/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:14:59 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/26 10:49:08 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	clear_buffer(char *buf, int start)
{
	while (start < BUFFER_SIZE)
		buf[start++] = '\0';
}

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
	{
		free(old_str);
		return (NULL);
	}
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
