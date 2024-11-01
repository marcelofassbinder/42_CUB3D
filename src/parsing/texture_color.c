/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:47 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/30 15:31:24 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_texture_color(t_cub_data *cub)
{
	int		i;
	char	**file;

	file = cub->map->file;
	i = -1;
	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") && !cub->map->north)
			cub->map->north = get_info(file[i], 2);
		else if (ft_strstr(file[i], "SO ") && !cub->map->south)
			cub->map->south = get_info(file[i], 2);
		else if (ft_strstr(file[i], "EA ") && !cub->map->east)
			cub->map->east = get_info(file[i], 2);
		else if (ft_strstr(file[i], "WE ") && !cub->map->west)
			cub->map->west = get_info(file[i], 2);
		else if (ft_strstr(file[i], "F ") && !cub->map->floor)
			cub->map->floor = get_info(file[i], 1);
		else if (ft_strstr(file[i], "C ") && !cub->map->ceiling)
			cub->map->ceiling = get_info(file[i], 1);
	}
	return (EXIT_SUCCESS);
}

int	is_valid_textures(t_cub_data *cub)
{
	int	fd;
	
	if (duplicate_texture(cub))
	{
		printf("Error!\nDuplicate texture\n");
		return (false);
	}
	if (!cub->map->north || !cub->map->south || !cub->map->east
		|| !cub->map->west)
		return (printf("Error!\nMissing texture\n"), false);
	fd = open(cub->map->north, O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->map->south, O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->map->east, O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->map->west, O_RDONLY);
	if (fd < 0)
		return (false);
	return (true);
}

int	duplicate_texture(t_cub_data *cub)
{
	char	**file;
	int		i;
	int		j;

	i = -1;
	file = cub->map->file;
	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") || ft_strstr(file[i], "SO ")
			|| ft_strstr(file[i], "EA ") || ft_strstr(file[i], "WE ")
			|| ft_strstr(file[i], "F ") || ft_strstr(file[i], "C "))
		{
			j = i;
			while (file[++j])
				if ((ft_strstr(file[i], "NO ") && ft_strstr(file[j], "NO "))
				|| (ft_strstr(file[i], "SO ") && ft_strstr(file[j], "SO "))
				|| (ft_strstr(file[i], "EA ") && ft_strstr(file[j], "EA "))
				|| (ft_strstr(file[i], "WE ") && ft_strstr(file[j], "WE "))
				|| (ft_strstr(file[i], "F ") && ft_strstr(file[j], "F "))
				|| (ft_strstr(file[i], "C ") && ft_strstr(file[j], "C ")))
					return (true);
		}
	}
	return (false);
}
