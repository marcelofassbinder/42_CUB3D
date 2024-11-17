/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/17 15:41:59 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

//encontrar o .cub no final do nome do arquivo
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

int	parsing(t_cub *cub, char *argv)
{
	int	end_infos;
	
	if (!cub)
		return (EXIT_FAILURE);
	cub->map->file = get_matrix_from_file(cub, argv);
	if (!cub->map->file)//precisa dessa checagem?
		return (printf("Error!\nEmpty file\n"));//criar funcao para msg de erro e frees
	end_infos = init_texture_color(cub);
	if (!is_valid_textures(cub))
		return (EXIT_FAILURE);//printf("Error!\nInvalid texture\n"));
	//varificar se tem alguma linha escrita a mais
	if (!is_valid_colors(cub))
		return (printf("Error!\nInvalid color\n"));
	cub->map->map_array = extract_map(cub, cub->map->file, end_infos);//ERRO: vai aceitar /n la no meio do mapa
	if (!cub->map->map_array)
		return (EXIT_FAILURE);//printf("Error\nInvalid character in map\n"));
	if (find_player_position(cub) || !closed_by_walls(cub, cub->map->map_array))
		return (EXIT_FAILURE);//printf("Error\nInvalid map\n"));
	//dar free da matrix cub->map->file
	//lembrar de dar free da matriz cub->map->map_array
	define_player_vectors(cub);
	define_initial_rotation(cub);
	return (EXIT_SUCCESS);
}

char	**get_matrix_from_file(t_cub *cub, char *file)
{
	char **matriz;
	char *line;
	int i;

	matriz = ft_calloc(sizeof(char *), count_lines(file) + 1);
	if (!matriz)
		return (NULL);
	line = NULL;
	i = 0;
	while (42)
	{
		line = get_next_line(cub->map->fd);
		if (!line)
			break ;
		matriz[i++] = ft_strdup(line);
		free(line);
	}
	close(cub->map->fd);
	return (matriz);
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
	return (counter);
}
