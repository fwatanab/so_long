#include "../inc/so_long.h"

static t_player	search_player(t_vars *vars)
{
	t_player	player;
	int			tmp;
	size_t		p_count;
	size_t		count;
	size_t		i;

	i = 0;
	tmp = vars->map_y / 40;
	count = 0;
	while (tmp--)
	{
		p_count = my_strchrlen(vars->map[i], 'P');
		if (p_count != 0)
			break ;
		i++;
		count++;
	}
	player.p_x = p_count;
	player.p_y = count;
	return (player);
}

static void	movement_player(t_vars *vars, char c)
{
	t_player	player;

	player = search_player(vars);
	ft_printf("%d\t%d\n", player.p_x, player.p_y);
	c = '0';
}

static void	close_window(t_vars *vars)
{
	free(vars->map);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
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
//	mlx_hook(vars->mlx);
	mlx_key_hook(vars->mlx_win, key_hook, vars);
//	mlx_loop_hook(vars->mlx, key_hook, vars);
}
