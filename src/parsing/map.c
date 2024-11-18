/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:22:29 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/18 17:46:08 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	**extract_map(t_cub *cub, char **file, int y)
{
	char	**map;
	int		size;

	size = map_size_valid_char(file, y);
	if (!size)
		return (printf("Error\nInvalid character in map\n"), NULL);
	cub->map.map_height = size;
	map = ft_calloc(sizeof(char **), size + 1);
	if (!map)
		return (error_message("Malloc failed in map struct!"), panic(cub), NULL);
	size = 0;
	while (empty_line(file[y]))
		y++;
	while (file[y])
	{
		if (empty_line(file[y])/*  && file[y + 1] && !empty_line(file[y + 1]) */)
			return (printf("Error\nEmpty line on map\n"), NULL);
		map[size++] = ft_strtrim(file[y], "\n");
		y++;
		//printf("%s\n", map[size - 1]);
	}
	return (map);
}

int	empty_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
	return (true);
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

int	find_player_position(t_cub *cub)
{
	char	**map;
	int 	y;
	int 	x;

	map = cub->map.map_array;
	y = -1;
	while (++y < cub->map.map_height)
	{
		x = -1;
		while (++x < ft_strlen(map[y]))
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (cub->player_char)
					return (printf("Error\nDuplicate player position\n"));
				cub->player_char = map[y][x];
				cub->player_position.x = x;
				cub->player_position.y = y;
			}
		}
	}
	if (!cub->player_char)
		return (printf("Error\nNo player position\n"));
	return (EXIT_SUCCESS);
}

