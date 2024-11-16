/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:56:06 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 22:18:16 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_bonus.h"

int	ray_casting_bonus(t_cub *cub)
{
	if (!cub->start_game)
		return (0);
	int ray_id = -1;
	while (++ray_id < WIDTH)
	{
		t_ray *ray;

		ray = calculate_ray(cub, ray_id);
		while (42)
		{
			increment_to_next_intersection(ray);
			if (cub->map->map_array[ray->map_y][ray->map_x] == WALL)
				break ;
		}
		calculate_wall_distance(ray);
		draw_floor_ceiling(cub, ray);
		draw_textures(cub, ray);
		free(ray);
	}
	minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->image->img, 0, 0);
	return (1);
	//mlx_destroy_image(cub->mlx_ptr, cub->image->img);
}

int	minimap(t_cub *cub)
{
	int x;
	int y;

	y = 0;
	while(y < cub->map->map_height)
	{
		x = 0;
		while(x < ft_strlen(cub->map->map_array[y]))
		{
			if (cub->map->map_array[y][x] == '1')
				render_element_minimap(cub, x, y, 0x48116E);
			else if (cub->map->map_array[y][x] == '0' || ft_strchr("NSWE", cub->map->map_array[y][x]))
				render_element_minimap(cub, x, y, 0xEBE9FC);
			x++;
		}
		y++;
	}
	render_player_minimap(cub);
	return (1);
}

void	render_element_minimap(t_cub *cub, int x, int y, int color)
{
	int h;
	int w;
	
	h = 0;
	while(h < MINMAP_SQUARE)
	{
		w = 0;
		while (w < MINMAP_SQUARE)
		{
			my_mlx_pixel_put(cub->image, w + (x * MINMAP_SQUARE), h + (y * MINMAP_SQUARE),  color);
			w++;
		}
		h++;
	}
}

void	render_player_minimap(t_cub *cub)
{
	t_coordinate player_minimap;
	int sphere_ray;
	int x;
	int y;

	player_minimap.x = cub->player_position->x * MINMAP_SQUARE;
	player_minimap.y = cub->player_position->y * MINMAP_SQUARE;
	sphere_ray = 4;
	x = -sphere_ray;
	while (x <= sphere_ray)
	{
		y = -sphere_ray;
		while (y <= sphere_ray)
		{
			if (x * x + y * y <= sphere_ray * sphere_ray)
				my_mlx_pixel_put(cub->image, player_minimap.x + x, player_minimap.y + y, 0xFF0000);
			y++;
		}
		x++;
	}
}

/* void	render_rays_minimap(t_cub *cub)
{
	//a desenvolver
} */
