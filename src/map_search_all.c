/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_search_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:01:27 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/25 17:14:02 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	map_search_all(char **argv, t_vars vars)
{
	t_player	player;

	vars = import_map(argv, vars);
	vars = set_null(vars);
	player = search_player(&vars);
	while (vars.map[player.p_y][player.p_x] != '1')
	{
		if (vars.c_count == 0 && vars.map[player.p_y][player.p_x] == 'E')
		{
			all_free(vars.map);
			return ;
		}
		else if (vars.map[player.p_y][player.p_x] == 'C')
		{
//			player.visited[player.p_y][player.p_x] = 1;
			vars.c_count--;
			player.p_y++;
		}
		else if (vars.map[player.p_y][player.p_x] != 'E')
		{
//			player.visited[player.p_y][player.p_x] = 1;
			player.p_y++;
		}
	}
	all_free(vars.map);
//	error();
}
