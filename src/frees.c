/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:35:17 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/08 17:51:04 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_matriz(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
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
	free_matriz(cub->map->file);
	free_matriz(cub->map->map_array);
	free(cub->map->floor);
	free(cub->map->ceiling);
	free_textures(cub);
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
		free(cub->textures->files[i]);
		free_image_struct(cub, &cub->textures->images[i]);	
	}
	free(cub->textures);
}

void	free_image_struct(t_cub *cub, t_image *image)
{
	mlx_destroy_image(cub->mlx_ptr, image->img);
	//free(image);
}
