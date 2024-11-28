/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:14:47 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/28 19:47:46 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

void	closed_by_walls(t_cub *cub, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				continue ;
			if ((map[y][x] == ' ' || map[y][x] == '\t')
				&& (!find_wall_up_down(cub, map, y, x)
				|| !find_wall_horizontaly(map, y, x)))
				return (panic (cub, "Map not closed by walls"));
			else if (((y == 0 || y == cub->map.map_height - 1)
					&& (map[y][x] != '1' && map[y][x] != ' '
				&& map[y][x] != '\t')) || ((x == 0
				|| x == ft_strlen(map[y]) - 1) && (map[y][x] != '1'
				&& map[y][x] != ' ' && map[y][x] != '\t')))
				return (panic(cub, "Map not closed by walls"));
		}
	}
	return ;
}

int	find_wall_horizontaly(char **map, int y, int x)
{
	int	initial_x;

	initial_x = x;
	while (x < ft_strlen(map[y]) && map[y][x])
	{
		if (map[y][x] == ' ' || map[y][x] == '\t')
			x++;
		else if (map[y][x] == '1')
			break ;
		else
			return (false);
	}
	x = initial_x;
	while (x >= 0 && map[y][x])
	{
		if (map[y][x] == ' ' || map[y][x] == '\t')
			x--;
		else if (map[y][x] == '1')
			return (true);
		else
			return (false);
	}
	return (true);
}

int	find_wall_up_down(t_cub *cub, char **map, int y, int x)
{
	int	initial_y;

	initial_y = y;
	while (y < cub->map.map_height && map[y][x])
	{
		if (map[y][x] == ' ' || map[y][x] == '\t')
			y++;
		else if (map[y][x] == '1')
			break ;
		else
			return (false);
	}
	y = initial_y;
	while (y >= 0 && map[y][x])
	{
		if (map[y][x] == ' ' || map[y][x] == '\t')
			y--;
		else if (map[y][x] == '1')
			return (true);
		else
			return (false);
	}
	return (true);
}
