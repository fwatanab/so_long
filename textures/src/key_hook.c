/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:04:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/27 15:07:41 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	close_window(t_vars *vars)
{
	all_free(vars->map);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close_window(vars);
	else if (keycode == W || keycode == UP)
		movement_player(vars, 'w');
	else if (keycode == A || keycode == LEFT)
		movement_player(vars, 'a');
	else if (keycode == S || keycode == DOWN)
		movement_player(vars, 's');
	else if (keycode == D || keycode == RIGHT)
		movement_player(vars, 'd');
	return (0);
}

void	hook(t_vars *vars)
{
	vars->walk_count = 0;
	mlx_hook(vars->mlx_win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->mlx_win, 17, 1L << 0, close_window, vars);
}
