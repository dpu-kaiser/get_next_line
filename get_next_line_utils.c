/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:14:59 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/21 15:22:40 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char * str_realloc(char *str, size_t size)
{
	char *result;
	size_t i;

	result = malloc(size);
	if (!result)
	{
		free(str);
		return NULL;
	}
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	while (i < size)
		result[i++] = '\0';
	return result;
}
