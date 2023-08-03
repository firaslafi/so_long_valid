/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:05:22 by flafi             #+#    #+#             */
/*   Updated: 2023/08/03 23:33:29 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	find_player_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
			{
				map->player->pos_row = i;
				map->player->pos_col = j;
				return (1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

void	ft_memfree(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_map_init(char **argv, t_map *map)
{
	map->c_steps = 0;
	check_map_extension(argv);
	fill_map(argv, map);
	map_is_rectangular(map->map, map->rows);
	verify_map_elements(map->map);
	elements_count_validation(map);
	wall_check(map->map, map->rows);
	find_player_pos(map);
	ft_check_valid_path(map, map->player->pos_row, map->player->pos_col);
	map->mlx = mlx_init(map->cols * 32, map->rows * 32, "so_long", false);
	if (!map->mlx)
		ft_error("mlx init failed");
}
