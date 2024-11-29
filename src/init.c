/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:57:54 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/29 16:18:24 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_cub	*init_cub_struct(void)
{
	t_cub	*cub;

	cub = ft_calloc(sizeof(t_cub), 1);
	if (!cub)
		return (error_message("Malloc fail in cub struct!"), panic(cub), NULL);
	cub->map.cub = cub;
	cub->start_game = false;
	cub->has_bullet = true;
	cub->shot = 0;
	cub->reload = 40;
	cub->mouse_x = WIDTH / 2;
	cub->walk = 0;
	cub->fixed_mouse_center = true;
	cub->door_is_open = false;
	return (cub);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (error_message("MLX connection failed!"), panic(cub));
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (!cub->mlx_win)
		return (error_message("MLX window creation failed!"), panic(cub));
	init_new_image(cub, &cub->image, WIDTH, HEIGHT);
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

void	init_textures(t_cub *cub)
{
	int		i;

	i = -1;
	while (++i < 4)
		init_image_xpm(cub, &cub->textures.images[i], cub->textures.files[i]);
	init_image_xpm(cub, &cub->textures.images[4], "./textures/door.xpm");
}
