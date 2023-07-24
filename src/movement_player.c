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

static void	move_left_right(t_vars *vars, char c)
{
	t_player	player;

	player = search_player(vars);
	if (c == 'a')
	{
		if (vars->map[player.p_y][player.p_x - 1] != '1')
		{
			vars->map[player.p_y][player.p_x - 1] = 'P';
			vars->map[player.p_y][player.p_x] = '0';
		}
	}
	if (c == 'd')
	{
		if (vars->map[player.p_y][player.p_x + 1] != '1')
		{
			vars->map[player.p_y][player.p_x + 1] = 'P';
			vars->map[player.p_y][player.p_x] = '0';
		}
	}
}

static void	move_up_down(t_vars *vars, char c)
{
	t_player	player;

	player = search_player(vars);
	if (c == 'w')
	{
		if (vars->map[player.p_y - 1][player.p_x] != '1')
		{
			vars->map[player.p_y - 1][player.p_x] = 'P';
			vars->map[player.p_y][player.p_x] = '0';
		}
	}
	if (c == 's')
	{
		if (vars->map[player.p_y + 1][player.p_x] != '1')
		{
			vars->map[player.p_y + 1][player.p_x] = 'P';
			vars->map[player.p_y][player.p_x] = '0';
		}
	}
}

void	movement_player(t_vars *vars, char c)
{
	if (c == 'w' || c == 's')
		move_up_down(vars, c);
	else if (c == 'a' || c == 'd')
		move_left_right(vars, c);
	create_map(*vars);
	vars->walk_count++;
	ft_printf("%d歩目\n", vars->walk_count);
}
