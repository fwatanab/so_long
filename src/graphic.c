/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:24:18 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/20 19:01:06 by fwatanab         ###   ########.fr       */
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

//static t_vars	import_map(char **argv, t_vars vars)
//{
//	int		fd;
//	char	*line;
//	int		tmp;
//
//	fd = open(argv[1], O_RDONLY);
//	if (fd == -1)
//		error();
//	tmp = vars.map_y / 40;
//	while (tmp--) 
//	{
//		if (tmp == vars.map_y / 40 - 1)
//			vars.map = get_next_line(fd);
//		else
//		{
//			line = get_next_line(fd);
//			vars.map = my_strjoin(vars.map, line);
//		}
//		if (!vars.map)
//		{
//			free(vars.map);
//			error_map(fd);
//		}
//	}
//	close(fd);
//	return (vars);
//}

static t_vars	import_map(char **argv, t_vars vars)
{
	int		fd;
	int		tmp;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	tmp = vars.map_y / 40;
	i = 0;
	vars.map = (char **)malloc(sizeof(char *));
	if (!vars.map)
		error_map(fd);
	while (tmp--)
	{
		vars.map[i] = (char *)malloc(sizeof(char) * (vars.map_x / 40 + 1));
		if (!vars.map[i])
			error_map(fd);
		vars.map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
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
	vars = import_map(argv, vars);
	hook(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
