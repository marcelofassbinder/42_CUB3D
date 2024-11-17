/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:17 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/17 18:11:20 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
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
	free(map);
}

void	free_image_struct(t_cub *cub, t_image *image)
{
	if (image->img)
		mlx_destroy_image(cub->mlx_ptr, image->img);
	free(image);
}

void	panic(t_cub *cub)
{
	if (!cub)
		exit(EXIT_FAILURE);
	if (cub->player_position)
		free(cub->player_position);
	if (cub->player_dir)
		free(cub->player_dir);
	if (cub->plane)
		free(cub->plane);
	if (cub->map)
		free_map_struct(cub->map);
	if (cub->textures)
		free_textures(cub);
	if (cub->image)
		free_image_struct(cub, cub->image);
	if (cub->initial)
		free_image_struct(cub, cub->initial);
	if (cub->mlx_window)
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_window);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free(cub);
	exit(EXIT_FAILURE);
}

/* typedef struct			s_cub {

	void				*mlx_ptr;
	void				*mlx_window;
	char				player_char;
	t_coordinate		*player_position;
	double				player_angle_rad;
	t_coordinate		*player_dir;
	t_coordinate		*plane;
	t_map				*map;
	t_image 			*image;
	t_text				*textures;
	int 				rotation;
	
}						t_cub;
 */

void	free_all_allocated_memory(t_cub *cub)
{
	free(cub->player_position);
	free(cub->player_dir);
	free(cub->plane);
	
	free_textures(cub);
	mlx_destroy_image(cub->mlx_ptr, cub->image->img);
	free(cub->image);
	free(cub->map);
	mlx_destroy_window(cub->mlx_ptr, cub->mlx_window);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free(cub);
}
/* 
typedef struct			s_image {

	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int 				line_len;
	int 				endian;

}						t_image; */

void	free_textures(t_cub *cub)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub->textures->files[i])
			free(cub->textures->files[i]);
		if (cub->textures->images[i].img)
			mlx_destroy_image(cub->mlx_ptr, cub->textures->images[i].img);
	}
	free(cub->textures);
}

void	error_message(char *str)
{
	write(STDERR_FILENO, "Error!\n", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}
