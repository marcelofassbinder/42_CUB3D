/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:22:29 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/05 20:50:47 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	**extract_map(char **file, int i)
{
	char	**map;
	int		j;
	int		size;

	size = map_size_valid_char(file, i);
	if (!size)
		return (NULL);
	map = ft_calloc(sizeof(char **), size);
	size = 0;
	while (file[++i])
	{
		j = -1;
		while(file[i][++j])
			if (j == 0 && file[i][j] == '\n')
				i++;
		map[size++] = ft_strtrim(file[i], "\n");
		//printf("%s\n", map[size - 1]);
	}
	return (map);
}

int	map_size_valid_char(char **file, int i)
{
	int	j;
	int	size;
	int	save_start;

	size = 0;
	save_start = i;
	while (file[++i])
	{
		j = -1;
		while(file[i][++j])
		{
			if (file[i][j] != ' ' && file[i][j] != '\t'
				&& file[i][j] != '\n' && file[i][j] != '1'
				&& file[i][j] != '0' && file[i][j] != 'N'
				&& file[i][j] != 'S' && file[i][j] != 'E'
				&& file[i][j] != 'W')
				return (0);
			if (j == 0 && file[i][j] == '\n')
				save_start++;
		}
	}
	return (i - save_start - 1);
}

int	find_player_position(t_cub_data *cub)
{
	char	**map;
	int 	y;
	int 	x;

	map = cub->map->map_array;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (cub->player_char)
					return (printf("Error\nDuplicate player position\n"));
				cub->player_char = map[y][x];
				cub->player_pos_X = x;
				cub->player_pos_Y = y;
			}
		}
	}
	if (!cub->player_char)
		return (printf("Error\nNo player position\n"));
	return (EXIT_SUCCESS);
}

int	closed_by_walls(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			//ver primeiro se a primeira e a ultima linha sao 1
			if (map[y][x] == ' ' || map[y][x] == '\t')
				if (find_wall(map, y, x))
					return (false);
			//ver a primeira e a ultima coluna
				//se for espaco ou tab, procurar pelo 1
			if (y == 0 || !map[y + 1][0])
				if (map[y][x] == '0')
					return (printf("Error\nMap not closed by walls\n"), false);
			//se a posicao de cima ou de baixo foi espaço ou tab,
			//subir ou descer ate achar o 1
		}
		printf("y -> %i linha -> %s\n", y, map[y]);
	}
	return (true);
}

int	find_wall(char **map, int y, int x)
{
	//pode ter espaço no meio do mapa??
	if (y == 0)
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
				return (printf("Error\nMap not closed by walls\n"));
			if (map[y][x] == '1')
				return (EXIT_SUCCESS);
			//if (map[y][x] == ' ' || map[y][x] == '\t')
			y++;
		}
	}
	if (!map[y + 1][0])
	{
		while (map[y][x])
		{
			if (map[y][x] == '0')
				return (printf("Error\nMap not closed by walls\n"));
			if (map[y][x] == '1')
				return (EXIT_SUCCESS);
			//if (map[y][x] == ' ' || map[y][x] == '\t')
			y--;
		}
	}
	return (EXIT_SUCCESS);
}
