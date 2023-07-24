/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:30:20 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/24 19:41:06 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	error_map(int fd)
{
	ft_printf("Error\n");
	close(fd);
	exit(EXIT_FAILURE);
}

void	error(void)
{
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

void	all_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
