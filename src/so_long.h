/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:19:01 by flafi             #+#    #+#             */
/*   Updated: 2023/07/30 22:57:31 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H


#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
# include "../libft/libft.h"
#include "../getnextline/get_next_line.h"
#include "../MLX42/include/MLX42/MLX42.h"
// replace it with my own printf
# include "../printf/ft_printf.h"

#define FLOOR_PATH "../assets/floor.xpm42"
#define WALL_PATH "../assets/wall.xpm42"
#define COIN_PATH "../assets/coin.xpm42"
#define PLAYER_PATH "../assets/player.xpm42"
#define EXIT_PATH "../assets/exit.xpm42"

typedef struct s_player
{
    int pos_row;
    int pos_col;
    
} t_player;

typedef struct s_graphics
{
    mlx_image_t *floor_img;
    mlx_image_t *exit_img;
    mlx_image_t *coin_img;
    mlx_image_t *player_img;
    mlx_image_t *wall_img;
} t_graphics;

typedef struct s_map
{
    int rows;
    int cols;
    int c_count;
    int c_steps;
    char **map;
    mlx_t *mlx;
    t_player *player;
    t_graphics *var;
} t_map;



int check_map_extension(char** argv);
int map_is_rectangular(char **map, int rows);
int verify_map_elements(char **map);
int elements_count(char **map, char c);
int elements_count_validation(t_map *map);
int full_line_check(char **map, int arr_len);
int wall_firstlast_check(char **map, int arr_len, int i, int len);
int wall_check(char **map, int arr_len);
int	ft_check_valid_path(t_map *map, int y, int x);
void ft_error(char *str); // new from here
void	ft_init_img(t_graphics *var, mlx_t *mlx);
void	ft_print_map(t_map *map);

#endif