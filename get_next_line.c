/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:13:51 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/21 13:16:45 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static int	copy_str(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(len + 1);
	if (result)
	{
		result[len] = '\0';
		len = copy_str(result, s1);
		len = copy_str(result + len, s2);
		return (result);
	}
	else
		return (0);
}

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
	int	start;
	int	i;
    int  read_len;
	char *old_result;

    read_len = -2;
	if (!buffer[0])
		read_len = read(fd, buffer, BUFFER_SIZE);
	len = get_next_line_len(buffer);
	if (!len)
		return (result);
	if (len == -1)
	{
		if (!result)
		{
			result = malloc(BUFFER_SIZE);
			start = 0;
		}
		else
		{
			start = ft_strlen(result);
			old_result = result;
			result = ft_strjoin(result, malloc(BUFFER_SIZE));
			free(old_result);
		}
        if (!result)
            return NULL;
        i = 0;
        while (i < BUFFER_SIZE)
        {
            result[start + i] = buffer[i];
            i++;
        }
        i = 0;
        while (i < BUFFER_SIZE)
            buffer[i++] = 0;
        result = get_next_line_rec(fd, buffer, result);
		return (result);
	}
	else
	{
		if (!result)
		{
			result = malloc(len);
			start = 0;
		}
		else
		{
			start = ft_strlen(result);
			old_result = result;
			result = ft_strjoin(result, malloc(len));
			free(old_result);
		}
		if (!result)
			return (NULL);
		i = 0;
		while (i < len)
		{
			result[start + i] = buffer[i];
			i++;
		}
		i = 0;
		while (len < BUFFER_SIZE)
		{
			buffer[i] = buffer[len];
			buffer[len] = 0;
			i++;
			len++;
		}
		while (i < BUFFER_SIZE)
			buffer[i++] = 0;
        if (read_len == -2)
            result = get_next_line_rec(fd, buffer, result);
		return (result);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*result;

	result = NULL;
	result = get_next_line_rec(fd, buffer, result);
	return (result);
}
