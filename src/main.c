/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:24:18 by fwatanab          #+#    #+#             */
/*   Updated: 2023/08/02 21:10:04 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

t_vars	set_null(t_vars vars)
{
	int	tmp;
	int	i;
	int	j;

	tmp = vars.map_y / 40;
	i = 0;
	while (tmp--)
	{
		j = 0;
		while (vars.map[i][j] && vars.map[i][j] != '\n')
			j++;
		if (vars.map[i][j] == '\n')
			vars.map[i][j] = '\0';
		i++;
	}
	vars.map[i] = NULL;
	return (vars);
}

static t_vars	map_size(char **argv)
{
	t_vars	vars;
	int		fd;
	char	*line;
	size_t	x_size;
	size_t	y_size;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	line = get_next_line(fd);
	x_size = my_strnlen(line);
	y_size = 0;
	while (line)
	{
		if (my_strnlen(line) != x_size)
			error_map(fd);
		line = get_next_line(fd);
		y_size++;
	}
	if (x_size == y_size)
		error_map(fd);
	vars.map_x = (int)x_size * 40;
	vars.map_y = (int)y_size * 40;
	close(fd);
	return (vars);
}

t_vars	import_map(char **argv, t_vars vars)
{
	int		fd;
	int		tmp;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	tmp = vars.map_y / 40;
	i = 0;
	vars.map = (char **)malloc(sizeof(char *) * (tmp + 1));
	if (!vars.map)
		error_map(fd);
	while (tmp--)
	{
		vars.map[i] = (char *)malloc(sizeof(char) * (vars.map_x / 40 + 1));
		if (!vars.map[i])
		{
			all_free(vars.map);
			error_map(fd);
		}
		vars.map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		error();
	vars = map_size(argv);
	vars.c_count = checker_map(argv, vars);
	map_search_all(argv, vars);
	vars = import_map(argv, vars);
	vars = set_null(vars);
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.map_x, vars.map_y, "so_long");
	create_map(vars);
	hook(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
