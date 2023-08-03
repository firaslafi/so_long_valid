/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:57:17 by flafi             #+#    #+#             */
/*   Updated: 2023/08/03 23:08:47 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

mlx_image_t	*put_image_to_map(mlx_t *mlx, mlx_image_t *imgt, char *path)
{
	xpm_t		*xpm;
	mlx_image_t	*img;
	int			fd;

	if (imgt)
		mlx_delete_image(mlx, imgt);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_error("files failed to open or does not exists");
		return (0);
	}
	close(fd);
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		return (0);
	img = mlx_texture_to_image(mlx, &(xpm->texture));
	if (!img)
		return (0);
	mlx_delete_xpm42(xpm);
	return (img);
}

void	ft_init_img(t_graphics *var, mlx_t *mlx)
{
	var->floor_img = put_image_to_map(mlx, var->floor_img, FLOOR_PATH);
	if (!var->floor_img)
		ft_error("Floor image failed to init.");
	var->player_img = put_image_to_map(mlx, var->player_img, PLAYER_PATH);
	if (!var->player_img)
		ft_error("Player image failed to init.");
	var->wall_img = put_image_to_map(mlx, var->wall_img, WALL_PATH);
	if (!var->wall_img)
		ft_error("Wall image failed to init.");
	var->coin_img = put_image_to_map(mlx, var->coin_img, COIN_PATH);
	if (!var->coin_img)
		ft_error("Coin image failed to init.");
	var->exit_img = put_image_to_map(mlx, var->exit_img, EXIT_PATH);
	if (!var->exit_img)
		ft_error("Exit image failed to init.");
}

void	ft_print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (j < (size_t)map->cols)
		{
			if (map->map[i][j] == '1')
				mlx_image_to_window(map->mlx, map->var->wall_img, j * 32, i
					* 32);
			else if (map->map[i][j] == 'P')
				mlx_image_to_window(map->mlx, map->var->player_img, j * 32, i
					* 32);
			else if (map->map[i][j] == 'C')
				mlx_image_to_window(map->mlx, map->var->coin_img, j * 32, i
					* 32);
			else
				mlx_image_to_window(map->mlx, map->var->floor_img, j * 32, i
					* 32);
			if (map->map[i][j] == 'E' && map->c_count == 0)
				mlx_image_to_window(map->mlx, map->var->exit_img, j * 32, i
					* 32);
			j++;
		}
		i++;
	}
}
