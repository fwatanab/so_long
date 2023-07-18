/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:28:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/10 14:28:53 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	block_count(char *line, size_t frag, int fd)
{
	size_t	size;
	size_t	i;

	size = my_strnlen(line);
	if (frag == 0)
	{
		if (line[0] != '1' || line[size - 1] != '1')
			error_map(fd);
	}
	else
	{
		i = 0;
		while (line[i] && line[i] != '\n')
		{
			if (line[i] != '1')
				error_map(fd);
			i++;
		}
	}
}

static size_t	check_map_nbr(char *line, char c)
{
	size_t	i;
	size_t	frag;

	i = 0;
	frag = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == c)
			frag++;
		i++;
	}
	return (frag);
}

static void	check_block(char **argv, t_vars vars)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	i = 0;
	while (i < vars.map_y / 40)
	{
		line = get_next_line(fd);
		if (i == 0 || i == vars.map_y / 40 - 1)
			block_count(line, 1, fd);
		else
			block_count(line, 0, fd);
		i++;
	}
	close(fd);
}

void	checker_map(char **argv, t_vars vars)
{
	int		fd;
	char	*line;
	size_t	p_size;
	size_t	c_size;
	size_t	e_size;

	p_size = 0;
	c_size = 0;
	e_size = 0;
	check_block(argv, vars);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	line = get_next_line(fd);
	while (line)
	{
		p_size += check_map_nbr(line, 'P');
		c_size += check_map_nbr(line, 'C');
		e_size += check_map_nbr(line, 'E');
		line = get_next_line(fd);
	}
	if (p_size != 1 || c_size <= 0 || e_size != 1)
		error_map(fd);
	close(fd);
}
