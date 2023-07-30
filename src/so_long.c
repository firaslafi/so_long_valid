/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:18:28 by flafi             #+#    #+#             */
/*   Updated: 2023/07/30 22:59:36 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

int fill_map(char **argv, t_map *map)
{
    int fd;
    int rows_count;
    char *str;
    char *tmp;
    
    fd = open(argv[1], O_RDONLY);
	if (fd < 0)
    {
        ft_error("fd opening failed.");
        return (0);
    }
    rows_count = 0;
    tmp = get_next_line(fd);
    str = "";
    while(tmp)
    {
        str = ft_strjoin(str, tmp);
        tmp = get_next_line(fd);
        rows_count++;
    }
    str = ft_strjoin(str, "\n");
    map->map = ft_split(str, '\n');
    map->rows = rows_count;
    map->cols = ft_strlen(map->map[0]);
    free(str);
    free(tmp);
    return (1);
}
int find_player_pos(t_map *map)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while(map->map[i])
    {
        while(map->map[i][j])
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
void	ft_memfree(char **array) // recheck this
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


void ft_move(t_map *map, int row, int col)
{
	if(map->map[row][col] == '0' || map->map[row][col] == 'C' || map->map[row][col] == 'E')
		{
            if (map->map[row][col] == '0' || map->map[row][col] == 'C')
            {
                if (map->map[row][col] == 'C')
                    map->c_count--;
                map->map[map->player->pos_row][map->player->pos_col] = '0';
                map->map[row][col] = 'P';
                find_player_pos(map);
                ft_print_map(map);
            }
            if (map->map[row][col] == 'E')
            {
                if(map->c_count == 0)
                    exit(1);
                map->map[map->player->pos_row][map->player->pos_col] = 'E';
                map->map[row][col] = 'P';
                find_player_pos(map);
                ft_print_map(map);
            }
            ft_printf("number of movements is : %i\n", ++(map->c_steps));
		}
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

int main(int argc, char* argv[])
{
    t_map *map;

    map = (struct s_map*) malloc(sizeof(struct s_map));
	if (map == NULL)
		ft_error("Memory allocation for map failed.\n");
    map->player = (struct s_player*) malloc(sizeof(struct s_player));
    	if (map->player == NULL)
		ft_error("Memory allocation for player failed.\n");
    map->var = (struct s_graphics*) malloc(sizeof(struct s_graphics));
    if (map->var == NULL)
		ft_error("Memory allocation for var failed.\n");
    if (argc != 2)
	    {
            ft_error("Too many/few arguments\n");
            exit(0);
        }
    map->c_steps = 0;
    check_map_extension(argv);
    fill_map(argv, map);
    map_is_rectangular(map->map, map->rows);
    verify_map_elements(map->map);
    elements_count_validation(map);
    wall_check(map->map, map->rows);
    find_player_pos(map);
    ft_check_valid_path(map, map->player->pos_row, map->player->pos_col);
    // testing starting from here 
	
	map->mlx = mlx_init( map->cols * 32, map->rows * 32, "so_long", false);
	if (!map->mlx)
		ft_error("mlx init failed");
    ft_init_img(map->var, map->mlx);

    // ft_memfree(map->map);
    // free(map);
    // system("leaks a.out");
    ft_print_map(map);
    
    mlx_key_hook(map->mlx, ft_hook, map);
	mlx_loop(map->mlx);
	// mlx_terminate(mlx);
	return (0);
}

