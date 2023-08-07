/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:18:28 by flafi             #+#    #+#             */
/*   Updated: 2023/08/07 20:49:15 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill_map(char **argv, t_map *map)
{
	int		fd;
	int		rows_count;
	char	*str;
	char	*tmp;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_error("fd opening failed.");
		return (0);
	}
	rows_count = 0;
	tmp = get_next_line(fd);
	str = ft_strdup("");
	while (tmp)
	{
		str = ft_strjoin_gnl(str, tmp);
		free(tmp);
		tmp = get_next_line(fd);
		rows_count++;
	}
	map->map = ft_split(str, '\n');
	map->rows = rows_count;
	map->cols = ft_strlen(map->map[0]);
	return (free(str), free(tmp), 1);
}

void	ft_move(t_map *map, int row, int col)
{
	if (map->map[row][col] == '0' || map->map[row][col] == 'C')
	{
		if (map->map[row][col] == 'C')
			map->c_count--;
		map->map[map->player->pos_row][map->player->pos_col] = '0';
		map->map[row][col] = 'P';
		ft_printf("number of movements is : %i\n", ++(map->c_steps));
	}
	if (map->map[row][col] == 'E')
	{
		map->map[map->player->pos_row][map->player->pos_col] = '0';
		map->map[row][col] = 'P';
		ft_printf("number of movements is : %i\n", ++(map->c_steps));
	}
	if (map->c_count == 0 && row == map->exit->pos_row
		&& col == map->exit->pos_col)
	{
		ft_memfree(map->map);
		exit(1);
	}
	find_player_pos(map);
	ft_print_map(map);
}

void	ft_hook(mlx_key_data_t data, void *param)
{
	t_map	*map;

	map = param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (data.key == MLX_KEY_W && data.action == MLX_PRESS)
		ft_move(map, map->player->pos_row - 1, map->player->pos_col);
	if (data.key == MLX_KEY_S && data.action == MLX_PRESS)
		ft_move(map, map->player->pos_row + 1, map->player->pos_col);
	if (data.key == MLX_KEY_A && data.action == MLX_PRESS)
		ft_move(map, map->player->pos_row, map->player->pos_col - 1);
	if (data.key == MLX_KEY_D && data.action == MLX_PRESS)
		ft_move(map, map->player->pos_row, map->player->pos_col + 1);
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	map = (struct s_map *)malloc(sizeof(struct s_map));
	if (map == NULL)
		ft_error("Memory allocation for map failed.\n");
	if (argc != 2)
		ft_error("Too many/few arguments\n");
	ft_map_init(argv, map);
	ft_init_img(map->var, map->mlx);
	ft_print_map(map);
	mlx_key_hook(map->mlx, ft_hook, map);
	mlx_loop(map->mlx);
	return (0);
}
