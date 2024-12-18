/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:17 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 18:36:02 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	free_map_struct(t_map *map)
{
	if (map->file)
		free_matrix(map->file);
	if (map->map_array)
		free_matrix(map->map_array);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
}

void	free_gun(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 15)
	{
		if (cub->gun[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->gun[i].img);
	}
}

void	panic(t_cub *cub, char *str)
{
	if (!cub)
		exit(EXIT_FAILURE);
	free_map_struct(&cub->map);
	free_textures(cub);
	free_gun(cub);
	if (cub->image.img)
		mlx_destroy_image(cub->mlx_ptr, cub->image.img);
	if (cub->initial.img)
		mlx_destroy_image(cub->mlx_ptr, cub->initial.img);
	if (cub->mlx_win)
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free(cub);
	if (str)
	{
		write(STDERR_FILENO, "Error!\n", 7);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

void	free_textures(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (cub->textures.files[i])
			free(cub->textures.files[i]);
		if (cub->textures.images[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->textures.images[i].img);
	}
	if (cub->textures.images[4].img)
		mlx_destroy_image(cub->mlx_ptr, cub->textures.images[4].img);
}
