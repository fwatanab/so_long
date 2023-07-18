#include "../inc/so_long.h"

static void	movement_player(t_vars *vars, char c)
{
	char	*p_loc;

	c = 'a';
	p_loc = ft_strchr(vars->map, 'P');
	ft_printf("---> %s\n", p_loc);
}

static void	close_window(t_vars *vars)
{
	free(vars->map);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	ft_printf("---> %s\n", vars->map);
	if (keycode == ESC)
		close_window(vars);
	else if (keycode == W || keycode == UP)
	{
		ft_printf("wが押されました\n");
		movement_player(vars, 'w');
	}
	else if (keycode == A || keycode == LEFT)
		ft_printf("aが押されました\n");
	else if (keycode == S || keycode == DOWN)
		ft_printf("sが押されました\n");
	else if (keycode == D || keycode == RIGHT)
		ft_printf("dが押されました\n");
	return (0);
}
void	hook(t_vars *vars)
{
	ft_printf("---> %s\n", vars->map);
	mlx_key_hook(vars->mlx_win, key_hook, vars);
}
