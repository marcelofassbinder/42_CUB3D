/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:07:20 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/17 18:11:20 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	has_three_numbers(char *str)
{
	int	i;
	int	comma;

	i = -1;
	comma = 0;
	while (str[++i])
	{
		if (str[i] == ',')
		{
			comma++;
			i++;
		}
		if (!ft_isdigit_space_tab(str[i]))
			return (false);
	}
	if (comma != 2)
		return (false);
	return (true);
}

/**
 * @brief Checks if a character is a digit, space, or tab.
 *
 * @param c The character to be checked.
 * @return Returns 2048 if the character is a digit, space, or tab. Otherwise, returns 0.
 */
int	ft_isdigit_space_tab(int c)
{
	if ((c < 48 || c > 57) && (c != ' ' && c != '\t'))
		return (0);
	return (2048);
}

void	save_rgb(t_cub *cub)
{
	char **buf;

	buf = ft_split(cub->map->ceiling, ',');
	cub->map->c_rgb[0] = ft_atoi(buf[0]);
	cub->map->c_rgb[1] = ft_atoi(buf[1]);
	cub->map->c_rgb[2] = ft_atoi(buf[2]);
	free_matrix(buf);
	buf = ft_split(cub->map->floor, ',');
	cub->map->f_rgb[0] = ft_atoi(buf[0]);
	cub->map->f_rgb[1] = ft_atoi(buf[1]);
	cub->map->f_rgb[2] = ft_atoi(buf[2]);
	//printf("rgb -> %i %i %i\n", cub->map->c_rgb[0], cub->map->c_rgb[1], cub->map->c_rgb[2]);
	free_matrix(buf);
}

int	rgb_to_hex(int rgb[3])
{
    return (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}
