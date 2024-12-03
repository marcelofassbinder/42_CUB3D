/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 19:25:17 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

//search for ".cub" in the end of the file name
int	find_extension(char *map, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(map) - 4;
	j = 0;
	while (map[i] == ext[j])
	{
		if (map[i] == '\0' && ext[j] == '\0')
			return (true);
		i++;
		j++;
	}
	return (false);
}

void	parsing(t_cub *cub, char *argv)
{
	int	end_infos;

	cub->map.fd = open(argv, O_RDONLY);
	if (cub->map.fd < 0)
		return (panic(cub, "Invalid file!"));
	cub->map.file = get_matrix_from_file(cub, argv);
	if (!cub->map.file)
		return (panic(cub, "Empty file"));
	end_infos = init_texture_color_names(cub);
	is_valid_textures(cub);
	is_valid_colors(cub);
	cub->map.map_array = extract_map(cub, cub->map.file, end_infos);
	if (!cub->map.map_array)
		return (panic(cub, NULL));
	closed_by_walls(cub, cub->map.map_array);
	find_player_position(cub);
	define_player_vectors(cub);
	define_initial_rotation(cub);
	return ;
}

char	**get_matrix_from_file(t_cub *cub, char *file)
{
	char	**matrix;
	char	*line;
	int		i;

	matrix = ft_calloc(sizeof(char *), count_lines(file) + 1);
	if (!matrix)
		return (panic(cub, "Malloc fail in map matrix!"), NULL);
	line = NULL;
	i = 0;
	while (42)
	{
		line = get_next_line(cub->map.fd);
		if (!line)
			break ;
		matrix[i] = ft_strdup(line);
		if (!matrix[i])
			return ((free(line), free_matrix(matrix),
					panic(cub, "Malloc fail in map matrix line!"), NULL));
		free(line);
		i++;
	}
	close(cub->map.fd);
	return (matrix);
}

int	count_lines(char *file)
{
	int		counter;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = NULL;
	counter = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		counter++;
		free (line);
	}
	free (line);
	close (fd);
	return (counter);
}

void	find_player_position(t_cub *cub)
{
	char	**map;
	int		y;
	int		x;

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
					return (panic(cub, "Duplicate player position"));
				cub->player_char = map[y][x];
				cub->player_position.x = x + 0.5;
				cub->player_position.y = y + 0.5;
			}
		}
	}
	if (!cub->player_char)
		return (panic(cub, "No player position"));
	return ;
}
