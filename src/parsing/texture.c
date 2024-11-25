/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:28:47 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/23 17:09:00 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	init_texture_color_names(t_cub *cub)
{
	int		i;
	char	**file;

	file = cub->map.file;
	i = -1;
	while (file[++i])
	{
		if (ft_strstr(file[i], "NO ") && !cub->textures.files[0])
			cub->textures.files[0] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "EA ") && !cub->textures.files[1])
			cub->textures.files[1] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "SO ") && !cub->textures.files[2])
			cub->textures.files[2] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "WE ") && !cub->textures.files[3])
			cub->textures.files[3] = get_info(file[i], 2);
		else if (ft_strstr(file[i], "F ") && !cub->map.floor)
			cub->map.floor = get_info(file[i], 1);
		else if (ft_strstr(file[i], "C ") && !cub->map.ceiling)
			cub->map.ceiling = get_info(file[i], 1);
		if (cub->textures.files[0] && cub->textures.files[1] &&
				cub->textures.files[2] && cub->textures.files[3] &&
					cub->map.floor && cub->map.ceiling)
			return (++i);
	}
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

int	is_valid_textures(t_cub *cub)
{
	int	fd;
	
	if (duplicate_texture_or_color(cub))
	{
		printf("Error!\nDuplicate texture or color\n");
		return (false);
	}
	
	if (!cub->textures.files[0] || !cub->textures.files[1]
		|| !cub->textures.files[2] || !cub->textures.files[3])
		return (printf("Error!\nMissing texture\n"), false);
	fd = open(cub->textures.files[0], O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->textures.files[1], O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->textures.files[2], O_RDONLY);
	if (fd < 0)
		return (false);
	fd = open(cub->textures.files[3], O_RDONLY);
	if (fd < 0)
		return (false);
	return (true);
}

int	duplicate_texture_or_color(t_cub *cub)
{
	char	**file;
	int		i;
	int		j;

	i = -1;
	file = cub->map.file;
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

int	is_valid_colors(t_cub *cub)
{
	int	i;

	i = -1;
	if (!cub->map.ceiling || !cub->map.floor)
		return (printf("Error!\nMissing color\n"), false);
	if (!has_three_numbers(cub->map.ceiling)
		|| !has_three_numbers(cub->map.floor))
		return (printf("Error!\nInvalid color\n"), false);
	save_rgb(cub);
	while (++i <= 2)
		if (cub->map.c_rgb[i] > 255 || cub->map.f_rgb[i] > 255)
			return (printf("Error!\nNumber > 255\n"), false);
	cub->map.c_hex = rgb_to_hex(cub->map.c_rgb);
	cub->map.f_hex = rgb_to_hex(cub->map.f_rgb);
	return (true);
}
