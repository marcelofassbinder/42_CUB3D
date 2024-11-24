/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:56:06 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/24 16:01:56 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_bonus.h"

int	minimap(t_cub *cub)
{
	int x;
	int y;

	cub->minmap_square = WIDTH / 125;
	y = 0;
	while(y < cub->map.map_height)
	{
		x = 0;
		while(x < ft_strlen(cub->map.map_array[y]))
		{
			if (cub->map.map_array[y][x] == '1')
				draw_element_minimap(cub, x, y, 0x48116E);
			else if (cub->map.map_array[y][x] == '0' || ft_strchr("NSWE", cub->map.map_array[y][x]))
				draw_element_minimap(cub, x, y, 0xEBE9FC);
			x++;
		}
		y++;
	}
	draw_player_minimap(cub);
	draw_rays_minimap(cub);
	return (1);
}

void	draw_element_minimap(t_cub *cub, int x, int y, int color)
{
	int h;
	int w;
	
	h = 0;
	while(h < cub->minmap_square)
	{
		w = 0;
		while (w < cub->minmap_square)
		{
			my_mlx_pixel_put(&cub->image, w + (x * cub->minmap_square), h + (y * cub->minmap_square),  color);
			w++;
		}
		h++;
	}
}

void	draw_player_minimap(t_cub *cub)
{
	t_coordinate player_minimap;
	double sphere_ray;
	int x;
	int y;

	player_minimap.x = cub->player_position.x * cub->minmap_square;
	player_minimap.y = cub->player_position.y * cub->minmap_square;
	sphere_ray = cub->minmap_square / 3;
	x = -sphere_ray;
	while (x <= sphere_ray)
	{
		y = -sphere_ray;
		while (y <= sphere_ray)
		{
			if (x * x + y * y <= sphere_ray * sphere_ray)
				my_mlx_pixel_put(&cub->image, player_minimap.x + x, player_minimap.y + y, 0x032DFD);
			y++;
		}
		x++;
	}
}

void	draw_rays_minimap(t_cub *cub)
{
	t_coordinate ray;
	double		camera_x;
	int			ray_id;

	ray_id = 0;
	while(ray_id <= WIDTH)
	{
		camera_x = 2 * (ray_id / (double)WIDTH) - 1; // camera_x varia de -1 a 1
		ray.x = cub->player_dir.x + cub->plane.x * camera_x;
		ray.y = cub->player_dir.y + cub->plane.y * camera_x;
		draw_one_ray_minimap(cub, &ray);
		ray_id += 3;
	}
}

void	draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector)
{
	double i;
	t_coordinate ray;

	i = 0.4;
	while (42)
	{
		ray.x = (cub->player_position.x + (i * ray_vector->x));
		ray.y = (cub->player_position.y + (i * ray_vector->y));
		if (cub->map.map_array[(int)ray.y][(int)ray.x] != '0' && cub->map.map_array[(int)ray.y][(int)ray.x] != cub->player_char)
			break ;
		my_mlx_pixel_put(&cub->image, (ray.x * cub->minmap_square), (ray.y) * cub->minmap_square, 0xFFFF66);
		i+= 0.1;
	}
}
