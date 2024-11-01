/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:54 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/30 15:31:21 by ismirand         ###   ########.fr       */
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

int	parsing(t_cub_data *cub, char *argv)
{
	if (!cub)
		return (1);
	cub->map->file = get_matrix_from_file(cub, argv);
	if (!cub->map->file)//precisa dessa checagem?
		return (printf("Error!\nEmpty file\n"));//criar funcao para msg de erro
	init_texture_color(cub);
	if (!is_valid_textures(cub))
		return (printf("Error!\nInvalid texture\n"));
	//varificar se tem alguma linha escrita a mais
	//analisar se sao validas (F e C tem que ser numero e < 256 (??))
	//extrair o mapa do arquivo
	//analisar se o mapa e valido
	//dar free da matrix cub->map->file
	//lembrar de dar free da matriz cub->map->map_array
	return (0);
}

char	*get_info(char *file, int flag)
{
	int		i;
	char	*buf;
	
	i = 0;
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	//tem que analisar os casos de como pode vir escrito
	i += flag;
	buf = ft_strtrim(&file[i], " \n\t");
	return (buf);
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
	return (counter);
}
