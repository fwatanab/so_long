/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:24:10 by fwatanab          #+#    #+#             */
/*   Updated: 2023/07/08 14:49:31 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static t_data	*compare_map(t_vars vars, char c, int fd)
{
	t_data	img;
	int		img_x;
	int		img_y;

	if (c == 'P')
		img.img = mlx_xpm_file_to_image(vars.mlx, P_IMG_PLAYER, &img_x, &img_y);
	if (c == '0')
		img.img = mlx_xpm_file_to_image(vars.mlx, P_IMG_GRASS, &img_x, &img_y);
	if (c == '1')
		img.img = mlx_xpm_file_to_image(vars.mlx, P_IMG_WOOD, &img_x, &img_y);
	if (c == 'E')
		img.img = mlx_xpm_file_to_image(vars.mlx, P_IMG_DOOR, &img_x, &img_y);
	if (c == 'C')
		img.img = mlx_xpm_file_to_image(vars.mlx, P_IMG_ITEM, &img_x, &img_y);
	if (img.img == NULL)
		error_map(fd);
	return (img.img);
}

static void	put_map(t_vars vars, char *line, size_t k, int fd)
{
	t_data	img;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
	{
		img.img = compare_map(vars, line[i], fd);
		img.addr = mlx_get_data_addr(img.img, &img.pixel, &img.len, &img.end);
		mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, j, k);
		j += 40;
		i++;
	}
}

void	create_map(t_vars vars, char **argv)
{
	int		fd;
	char	*line;
	size_t	k;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error();
	line = get_next_line(fd);
	k = 0;
	while (line)
	{
		put_map(vars, line, k, fd);
		line = get_next_line(fd);
		k += 40;
	}
	close(fd);
}
