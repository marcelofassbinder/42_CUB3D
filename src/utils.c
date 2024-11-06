/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:22:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/10/28 16:03:32 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;
	int 	offset;
	
	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}


/**
 * @brief Finds the first occurrence of the substring `to_find` in the string `str`, 
 * ignoring leading spaces and tabs in `str`. 
 *
 * @return A pointer to the first occurrence of `to_find` in `str`, 
 * or NULL if `to_find` is not found.
 */
char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(to_find);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], to_find, len))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
