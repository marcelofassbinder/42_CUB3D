/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:57:54 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 22:07:07 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_cub *init_cub_struct(void)
{
	t_cub *cub;

	cub = ft_calloc(sizeof(t_cub), 1);
	if (!cub)
		return (NULL);
	cub->map = ft_calloc(sizeof(t_map), 1);
	cub->map->cub = cub;
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->player_position = ft_calloc(sizeof(t_coordinate), 1);
	cub->player_dir = ft_calloc(sizeof(t_coordinate), 1);
	cub->plane = ft_calloc(sizeof(t_coordinate), 1);
	cub->image = ft_calloc(sizeof(t_image), 1);
	cub->image->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image->addr = mlx_get_data_addr(cub->image->img, &cub->image->bits_per_pixel,
		&cub->image->line_len, &cub->image->endian);
	cub->textures = ft_calloc(sizeof(t_text), 1);
	cub->start_game = false;
	return (cub);
}

void	define_initial_rotation(t_cub *cub)
{
	if (cub->player_char == 'N')
	{
		cub->player_angle_rad = 0;
		cub->rotation = 0;
	}
	if (cub->player_char == 'E')
	{
		cub->player_angle_rad = PI / 2;
		cub->rotation = 12;
	}
	if (cub->player_char == 'S')
	{
		cub->player_angle_rad = PI;
		cub->rotation = 24;
	}
	if (cub->player_char == 'W')
	{	
		cub->player_angle_rad = 3 * PI / 2;
		cub->rotation = 36;
	}
}

void	define_player_vectors(t_cub *cub)
{
	if (cub->player_char == 'N' || cub->player_char == 'S')
	{
		cub->plane->x = 1;
		cub->plane->y = 0;
		cub->player_dir->x = 0;
		cub->player_dir->y = -1;
		if (cub->player_char == 'S')
		{
			cub->player_dir->y = 1;
			cub->plane->x = -1;
		}
	}
	else if (cub->player_char == 'W' || cub->player_char == 'E')
	{
		cub->plane->x = 0;
		cub->plane->y = -1;
		cub->player_dir->x = -1;
		cub->player_dir->y = 0;
		if (cub->player_char == 'E')
		{
			cub->player_dir->x = 1;
			cub->plane->y = 1;
		}
	}
}

void	define_textures(t_cub *cub)
{
	t_text *t;

	t = cub->textures;
	
	t->images[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->textures->files[0], &t->text_w[0], &t->text_h[0]);
	t->images[0].addr = mlx_get_data_addr(t->images[0].img, 
		&t->images[0].bits_per_pixel, &t->images[0].line_len, &t->images[0].endian);
	t->images[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->textures->files[1], &t->text_w[1], &t->text_h[1]);
	t->images[1].addr = mlx_get_data_addr(t->images[1].img, 
		&t->images[1].bits_per_pixel, &t->images[1].line_len, &t->images[1].endian);
	t->images[2].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->textures->files[2], &t->text_w[2], &t->text_h[2]);
	t->images[2].addr = mlx_get_data_addr(t->images[2].img,
		&t->images[2].bits_per_pixel, &t->images[2].line_len, &t->images[2].endian);
	t->images[3].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->textures->files[3], &t->text_w[3], &t->text_h[3]);
	t->images[3].addr = mlx_get_data_addr(t->images[3].img, 
		&t->images[3].bits_per_pixel, &t->images[3].line_len, &t->images[3].endian);
}
