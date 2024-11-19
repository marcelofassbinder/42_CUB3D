/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:57:54 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/19 17:13:42 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_cub *init_cub_struct(void)
{
	t_cub *cub;
	cub = ft_calloc(sizeof(t_cub), 1);
	if (!cub)
		return (error_message("Malloc failed in cub struct!"), panic(cub) , NULL);
	cub->map.cub = cub;
	cub->start_game = false;
	cub->shot = false;
	return (cub);
}

void	init_window(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return(error_message("MLX connection failed!"), panic(cub));
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!cub->mlx_window)
		return(error_message("MLX window creation failed!"), panic(cub));
	cub->image.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	if (!cub->image.img)
		return(error_message("Image creation failed!"), panic(cub));
	cub->image.addr = mlx_get_data_addr(cub->image.img, &cub->image.bits_per_pixel,
		&cub->image.line_len, &cub->image.endian);
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
		cub->plane.x = 0.66;
		cub->plane.y = 0;
		cub->player_dir.x = 0;
		cub->player_dir.y = -1;
		if (cub->player_char == 'S')
		{
			cub->player_dir.y = 1;
			cub->plane.x = -0.66;
		}
	}
	else if (cub->player_char == 'W' || cub->player_char == 'E')
	{
		cub->plane.x = 0;
		cub->plane.y = -0.66;
		cub->player_dir.x = -1;
		cub->player_dir.y = 0;
		if (cub->player_char == 'E')
		{
			cub->player_dir.x = 1;
			cub->plane.y = 0.66;
		}
	}
}

void	define_textures(t_cub *cub)
{
	t_text	t;
	int		i;

	t = cub->textures;
	i = -1;
	while (++i < 4)
	{
		t.images[i].img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->textures.files[i], &t.images[i].width, &t.images[i].height);
		if (!t.images[i].img)
			return(error_message("XPM to image conversion failed!"), panic(cub));
		t.images[i].addr = mlx_get_data_addr(t.images[i].img, 
			&t.images[i].bits_per_pixel, &t.images[i].line_len, &t.images[i].endian);
	}
	cub->textures = t;
}
