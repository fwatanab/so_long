/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:04:30 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/20 19:01:15 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

size_t	my_strnlen(const char *str)
{
	size_t	size;

	if (!str)
		error();
	size = 0;
	while (str[size] && str[size] != '\n')
		size++;
return (size);
}

size_t	my_strchrlen(const char *s, int c)
{
	size_t	i;
	size_t	n_count;

	if (!s)
		return (0);
	i = 0;
	n_count = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			n_count++;
		if (s[i] == (char)c)
			return (i - n_count);
		i++;
	}
	if ((char)c == '\0')
		return (i - n_count);
	return (0);
}

