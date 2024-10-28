/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/28 14:20:00 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

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

void	parsing(t_cub_data *cub, char *argv)
{
	if (!cub)
		return ;
	cub->map->file = get_matrix_from_file(cub, argv);
	if (!cub->map->file)//precisa dessa checagem?
		return ;//msg de erro?
	//pegar texturas e cores
	init_texture_color(cub);
	//analisar se sao validas
	//extrair o mapa do arquivo
	//analisar se o mapa e valido
	//dar free da matrix cub->map->file
	//lembrar de dar free da matriz cub->map->map_array
	return ;
}

void	init_texture_color(t_cub_data *cub)
{
	
}

/* int	parse_file(t_gm *game, int argc, char **argv)
{
	char	**cub;

	cub = get_mapfile_info(game, argv[1]);
	replace_tabs_to_space(cub);
	get_texture_and_color(game, cub);
	if (!is_texture_and_color_valid(game, cub)
		|| !is_openble_file(game->map->ntex, NULL, 4)
		|| !is_openble_file(game->map->stex, NULL, 4)
		|| !is_openble_file(game->map->etex, NULL, 4)
		|| !is_openble_file(game->map->wtex, NULL, 4))
		return (ft_free_matriz(cub), EXIT_FAILURE);
	extract_map(game, cub);
	if (!is_map_valid(game))
		return (ft_free_matriz(cub), EXIT_FAILURE);
	ft_free_matriz(cub);
	(void)argc;
	return (EXIT_SUCCESS);
} */

char	**get_matrix_from_file(t_cub_data *cub, char *file)
{
	char **map;
	char *line;
	int i;

	map = ft_calloc(sizeof(char *), count_lines(file) + 1);
	if (!map)
		return (NULL);
	line = NULL;
	i = 0;
	while (42)
	{
		line = get_next_line(cub->map->fd);
		if (!line)
			break ;
		map[i++] = ft_strdup(line);
		free(line);
	}
	close(cub->map->fd);
	return (map);
}


int	count_lines(char *file)
{
	int		counter;
	int		fd;
	char	*line;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error : fd < 0\n"), -1);//tratar erro desse retorno
	line = NULL;
	counter = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		counter++;
		free (line);
	}
	free (line);
	close (fd);
	printf("%i\n", counter);
	return (counter);
}
