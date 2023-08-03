/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_search_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:01:27 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 22:09:29 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static bool	check_road(t_vars *vars, int y, int x)
{
	if (vars->map[y][x] != '1' && vars->map[y][x] != 'N')
	{
		if (vars->map[y][x] == 'E')
			vars->e_count--;
		if (vars->map[y][x] == 'C')
			vars->c_count--;
		vars->map[y][x] = 'N';
		return (true);
	}
	return (false);
}

static void	search(t_vars *vars, int y, int x)
{
	if (!check_road(vars, y, x))
		return ;
	search(vars, y - 1, x);
	search(vars, y, x + 1);
	search(vars, y + 1, x);
	search(vars, y, x - 1);
}

void	map_search_all(char **argv, t_vars vars)
{
	t_player	player;

	vars = import_map(argv, vars);
	vars = set_null(vars);
	player = search_player(&vars);
	vars.e_count = 1;
	search(&vars, player.p_y, player.p_x);
	all_free(vars.map);
	if (vars.c_count == 0 && vars.e_count == 0)
		return ;
	error();
}
