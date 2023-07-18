/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:30:20 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/10 14:30:22 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	error_map(int fd)
{
	ft_printf("error\n");
	close(fd);
	exit(1);
}

void	error(void)
{
	ft_printf("error\n");
	exit(1);
}
