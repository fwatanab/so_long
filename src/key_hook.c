#include "../inc/so_long.h"

static void	movement_player(t_vars *vars, char c)
{
	char	*p_loc;
	size_t	p_count;

	c = 'a';
	p_count = my_strchrlen(vars->map, 'P');
	ft_printf("%d\n", (int)p_count);
	p_loc = ft_strchr(vars->map, 'P');
	ft_printf("%s\n", p_loc);
}

static void	close_window(t_vars *vars)
{
	free(vars->map);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == X_ESC)
		close_window(vars);
	else if (keycode == 'w'/*W*/ || keycode == X_UP)
	{
		ft_printf("wが押されました\n");
		movement_player(vars, 'w');
	}
	else if (keycode == 'a'/*A*/ || keycode == X_LEFT)
		ft_printf("aが押されました\n");
	else if (keycode == 's'/*S*/ || keycode == X_DOWN)
		ft_printf("sが押されました\n");
	else if (keycode == 'd'/*D*/ || keycode == X_RIGHT)
		ft_printf("dが押されました\n");
	return (0);
}
void	hook(t_vars *vars)
{
//	mlx_hook(vars->mlx);
	mlx_key_hook(vars->mlx_win, key_hook, vars);
//	mlx_loop_hook(vars->mlx, key_hook, vars);
}
