/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:24:45 by flafi             #+#    #+#             */
/*   Updated: 2023/08/03 23:09:52 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_extension(char **argv)
{
	int		i;
	char	*str;
	int		j;

	i = ft_strlen(argv[1]) - 4;
	str = ft_strdup(".ber");
	j = 0;
	while (str[j])
	{
		if (argv[1][i] == str[j])
		{
			j++;
			i++;
		}
		else
		{
			ft_error(".ber extension not valid\n");
			return (0);
		}
	}
	free(str);
	return (1);
}

int	map_is_rectangular(char **map, int rows)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(map[i]);
	while (rows)
	{
		if (len != ft_strlen(map[i]))
		{
			ft_memfree(map);
			ft_error("map is not rectangular\n");
			return (0);
		}
		i++;
		rows--;
	}
	return (1);
}

int	ft_valid_char(char str)
{
	if (str == '0' || str == '1' || str == 'P' || str == 'E' || str == 'C')
		return (1);
	return (0);
}

int	verify_map_elements(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (ft_valid_char(map[i][j]))
				j++;
			else
			{
				ft_memfree(map);
				ft_error("map elements are not valid.\n");
				return (0);
			}
		}
		j = 0;
		i++;
	}
	return (1);
}
