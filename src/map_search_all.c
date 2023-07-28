/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_search_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:01:27 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/28 18:33:16 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	check(t_vars vars, int i, int j)
{
	if (i >= vars.map_y || j >= vars.map_x
		|| vars.map[i][j] == WALL || vars.map[i][j] == PASSED)
			return (0);
	return (1);
}

static int	search(t_vars vars, int s_i, int s_j)
{
	t_cie	cie;
	int		i;
	int		j;

	if (check(s_i, s_j) == 1)
		return (1);
	else
		vars.map[s_i][s_j] = PASSED;
	while (1)
	{
	}
	return (0);
}

void	map_search_all(char **argv, t_vars vars)
{
	t_player	player;

	vars = import_map(argv, vars);
	vars = set_null(vars);
	player = search_player(&vars);
	all_free(vars.map);
//	error();
}
