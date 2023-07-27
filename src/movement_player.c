/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:59:33 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/27 15:25:42 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

t_player	search_player(t_vars *vars)
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

static int	check_move(t_vars *vars, int y, int x)
{
	if (vars->map[y][x] != '1')
	{
		if (vars->c_count != 0 && vars->map[y][x] == 'E')
			return (-1);
		else if (vars->map[y][x] == 'E')
		{
			vars->map[y][x] = 'P';
			return (1);
		}
		else if (vars->map[y][x] == 'C')
			vars->c_count--;
		vars->map[y][x] = 'P';
		return (0);
	}
	return (-1);
}

void	movement_player(t_vars *vars, char c)
{
	t_player	player;
	int			r;

	player = search_player(vars);
	r = 0;
	if (c == 'w')
		r = check_move(vars, player.p_y - 1, player.p_x);
	else if (c == 'a')
		r = check_move(vars, player.p_y, player.p_x - 1);
	else if (c == 's')
		r = check_move(vars, player.p_y + 1, player.p_x);
	else if (c == 'd')
		r = check_move(vars, player.p_y, player.p_x + 1);
	if (r == 0 || r == 1)
	{
		vars->map[player.p_y][player.p_x] = '0';
		vars->walk_count++;
		ft_printf("%d歩目\n", vars->walk_count);
	}
	create_map(*vars);
	if (r == 1)
	{
		ft_printf("GAME CLEAR\n");
		close_window(vars);
	}
}
