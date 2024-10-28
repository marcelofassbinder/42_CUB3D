/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/28 16:25:11 by ismirand         ###   ########.fr       */
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
	//analisar se sao validas (F e C tem que ser numero e < 256 (??))
	//extrair o mapa do arquivo
	//analisar se o mapa e valido
	//dar free da matrix cub->map->file
	//lembrar de dar free da matriz cub->map->map_array
	return ;
}

void	init_texture_color(t_cub_data *cub)
{
	int		i;
	char	**file;

	file = cub->map->file;
	i = 0;
	while (file[i])
	{
		if (ft_strstr(file[i], "NO ") && !cub->map->north)
			cub->map->north = get_info(file[i], "NO ");
		else if (ft_strstr(file[i], "SO ") && !cub->map->south)
			cub->map->south = get_info(file[i], "SO ");
		else if (ft_strstr(file[i], "EA ") && !cub->map->east)
			cub->map->east = get_info(file[i], "EA ");
		else if (ft_strstr(file[i], "WE ") && !cub->map->west)
			cub->map->west = get_info(file[i], "WE ");
		else if (ft_strstr(file[i], "F ") && !cub->map->floor)
			cub->map->floor = get_info(file[i], "F ");
		else if (ft_strstr(file[i], "C ") && !cub->map->ceiling)
			cub->map->ceiling = get_info(file[i], "C ");
		i++;
	}
	return ;
	//se tiver a info mais de uma vez, retorna erro
}

char	*get_info(char *file, char *str)
{
	char	*info;
	int		size;

	printf("string-> %s\n", ft_strstr(file, str));
	size = ft_strlen(ft_strstr(file, str));
	printf("size-> %i\n", size);
	return (NULL);
}


char	**get_matrix_from_file(t_cub_data *cub, char *file)
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
	printf("%i\n", counter);
	return (counter);
}
