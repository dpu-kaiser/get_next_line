/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:14:59 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/25 11:53:28 by dkaiser          ###   ########.fr       */
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

char	*str_realloc(char *str, size_t size)
{
	char	*result;
	size_t	i;

	result = malloc(size);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	while (i < size)
		result[i++] = '\0';
	return (result);
}
