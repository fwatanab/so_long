/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:24:18 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/15 17:38:15 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

size_t	my_strnlen(const char *str)
{
	size_t	size;

	if (!str)
		error();
	size = 0;
	while (str[size] && str[size] != '\n')
		size++;
	return (size);
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

static t_vars	import_map(char **argv, t_vars vars)
{
	int		fd;
	char	*line;
	char	*str;
	int		tmp;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	tmp = vars.map_y / 40;
	while (tmp--)
	{
		if (tmp == vars.map_y / 40 - 1)
			str = get_next_line(fd);
		else
		{
			line = get_next_line(fd);
			str = my_strjoin(str, line);
		}
		if (!str)
			error_map(fd);
	}
	close(fd);
	vars.map = str;
	free(str);
	return (vars);
}

int	put_window(char **argv)
{
	t_vars	vars;

	vars = map_size(argv);
	checker_map(argv, vars);
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, vars.map_x, vars.map_y, "so_long");
	create_map(vars, argv);
	import_map(argv, vars);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
//	mlx_loop_hook(vars.mlx_win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
