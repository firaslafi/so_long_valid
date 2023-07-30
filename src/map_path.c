/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:43:43 by flafi             #+#    #+#             */
/*   Updated: 2023/07/30 23:00:13 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

char	**ft_mapcpy(char **map, int rows)
{
	int		i;
	char	**dest;

	dest = malloc((rows + 1) * (sizeof(char *)));
	if (!dest)
		return (NULL);
	i = 0;
	while (map[i])
	{
		dest[i] = ft_strdup(map[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	ft_fill(char **map_cpy, int rows, int cols)
{
	if (map_cpy[rows][cols] == '1' || map_cpy[rows][cols] == '*')
		return ;
	map_cpy[rows][cols] = '*';
	ft_fill(map_cpy, rows - 1, cols);
	ft_fill(map_cpy, rows + 1, cols);
	ft_fill(map_cpy, rows, cols - 1);
	ft_fill(map_cpy, rows, cols + 1);
}

int	ft_check_valid_path(t_map *map, int rows, int cols)
{
	char	**map_cpy;

	map_cpy = ft_mapcpy(map->map, map->rows);
	ft_fill(map_cpy, rows, cols);
	if (elements_count(map_cpy, 'C') != 0)
		{
            ft_error("no valid path\n");
            return (0);
        }
	if (elements_count(map_cpy, 'E') == 1)
		{
             ft_error("no valid path\n");
            return (0);
        }
	return (1);
}
