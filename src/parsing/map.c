/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:22:29 by ismirand          #+#    #+#             */
/*   Updated: 2024/12/02 15:41:41 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

char	**extract_map(t_cub *cub, char **file, int y)
{
	char	**map;
	int		size;
	int		line_size;

	size = map_size_valid_char(file, y, cub->is_bonus);
	if (!size)
		return (panic(cub, "Invalid character in map"), NULL);
	cub->map.map_height = size;
	line_size = find_biggest_line(file);
	map = ft_calloc(sizeof(char *), size + 1);
	if (!map)
		return (panic(cub, "Malloc fail in map struct!"), NULL);
	size = 0;
	while (empty_line(file[y]))
		y++;
	while (file[y])
	{
		if (empty_line(file[y]))
			return (free_matrix(map), panic(cub, "Empty line on map"), NULL);
		map[size] = get_map_line(file[y], line_size);
		size++;
		y++;
	}
	return (map);
}

//copies the line from the file to the map, taking out the '\n' in the end and
//adding spaces as needed to fit the line size
char	*get_map_line(char *file, int size)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(sizeof(char), size + 1);
	while (file[i] && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	while (i < size)
		line[i++] = ' ';
	return (line);
}

int	find_biggest_line(char **map)
{
	int	i;
	int	line;

	i = -1;
	line = 0;
	while (map[++i])
		if (ft_strlen(map[i]) > line)
			line = ft_strlen(map[i]);
	return (line);
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

int	map_size_valid_char(char **file, int i, bool is_bonus)
{
	int	j;
	int	size;
	int	save_start;

	size = 0;
	save_start = i;
	while (file[++i])
	{
		j = -1;
		while (file[i][++j])
		{
			if (file[i][j] != ' ' && file[i][j] != '\t'
				&& file[i][j] != '\n' && file[i][j] != WALL
				&& file[i][j] != FLOOR && file[i][j] != 'N'
				&& file[i][j] != 'S' && file[i][j] != 'E'
				&& file[i][j] != 'W' && file[i][j] != C_DOOR)
				return (0);
			if (!is_bonus && file[i][j] == C_DOOR)
				return (0);
			if (j == 0 && file[i][j] == '\n')
				save_start++;
		}
	}
	return (i - save_start - 1);
}
