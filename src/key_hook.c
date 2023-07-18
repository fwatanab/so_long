#include "../inc/so_long.h"

void	close_window(t_vars vars)
{
	mlx_destroy_window(vars.mlx, vars.mlx_win);
	ft_printf("end\n");
	exit(0);
}

int	key_hook(int keycode, t_vars vars)
{
	if (keycode == ESC)
		close_window(vars);
	else if (keycode == W || keycode == UP)
		ft_printf("wが押されました\n");
	else if (keycode == A || keycode == LEFT)
		ft_printf("aが押されました\n");
	else if (keycode == S || keycode == DOWN)
		ft_printf("sが押されました\n");
	else if (keycode == D || keycode == RIGHT)
		ft_printf("dが押されました\n");
	return (0);
}
