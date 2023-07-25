#include "../inc/so_long.h"

int	close_window(t_vars *vars)
{
	all_free(vars->map);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == X_ESC)
		close_window(vars);
	else if (keycode == 'w' || keycode == X_UP)
		movement_player(vars, 'w');
	else if (keycode == 'a' || keycode == X_LEFT)
		movement_player(vars, 'a');
	else if (keycode == 's' || keycode == X_DOWN)
		movement_player(vars, 's');
	else if (keycode == 'd' || keycode == X_RIGHT)
		movement_player(vars, 'd');
	return (0);
}
void	hook(t_vars *vars)
{
	vars->walk_count = 0;
	mlx_loop_hook(vars->mlx_win, key_hook, vars);
	mlx_hook(vars->mlx_win, 2, 1L<<0, key_hook, vars);
	mlx_hook(vars->mlx_win, 17, 1L<<0, close_window, vars);
//	mlx_expose_hook(vars->mlx_win, create_map, vars);
//	mlx_hook(vars->mlx_win, 25, 1L<<0, create_map, vars);
}
