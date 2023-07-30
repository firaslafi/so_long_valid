/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:07:56 by flafi             #+#    #+#             */
/*   Updated: 2023/07/30 22:58:50 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
int elements_count(char **map, char c)
{
	int i = 0;
	int j = 0;
	int count = 0;
	while(map[i])
	{
		while(map[i][j])
		{
			if(map[i][j] == c)
				{
					count++;
					j++;
				}
			else
				j++;
		}
		j = 0;
		i++;
	}
	return (count);
	
}
int elements_count_validation(t_map *map)
{
	map->c_count = elements_count(map->map, 'C');
	if(elements_count(map->map, 'P') != 1)
        ft_error("not found or multiple player!\n");
	if(elements_count(map->map, 'C') < 1)
		ft_error("No collectable alert!\n");
	if(elements_count(map->map, 'E') != 1)
        ft_error("not found or multiple exit alert!\n");
	return (1);
}
int full_line_check(char **map, int arr_len)
{
	int i;
	int j;
	
	i = 1;
	j = 0;
	while(map[0][j] && map[arr_len - 1][j])
	{
		if (map[0][j] == '1' && map[arr_len - 1][j] == '1')
			j++;
		else
		{
			ft_error("not valid wall\n");
			return (0);
		}
	}
	return (1);
}
int wall_firstlast_check(char **map, int arr_len, int i, int len)
{
	while(map[i][0] && i != arr_len - 1)
	{
		if (map[i][0] == '1' && map[i][len - 1] == '1')
			i++;
		else
		{
			ft_error("not valid wall\n");
			return (0);
		}
	}
	return (1);
}
int wall_check(char **map, int arr_len)
{
	int i;
	int j;
	int len;
	
	i = 1;
	j = 0;
	len = 1;
	if (!full_line_check(map, arr_len))
		return (0);
	while(map[0][i])
	{
		len++;
		i++;
	}
	i = 1;
	if(!wall_firstlast_check(map, arr_len, i, len))
		return (0);
	return (1);
}