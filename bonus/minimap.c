/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:56:06 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/18 21:32:36 by mfassbin         ###   ########.fr       */
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
			if (cub->map.map_array[ray->map_y][ray->map_x] == WALL)
				break ;
		}
		calculate_wall_distance(ray);
		draw_floor_ceiling(cub, ray);
		draw_textures(cub, ray);
		free(ray);
	}
	minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->image.img, 0, 0);
	return (1);
}

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

	draw_one_ray_minimap(cub, &cub->player_dir);
	ray.x = cub->player_dir.x - cos(cub->player_angle_rad - 0.0058); //pedir ajuda para belaaaa
	ray.y = cub->player_dir.y;
	draw_one_ray_minimap(cub, &ray);
	/* ray.x = -sin(cub->player_angle_rad);
	ray.y = -cos(cub->player_angle_rad);
	draw_one_ray_minimap(cub, &ray);  */

}

void	draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector)
{
	double i;
	t_coordinate ray;
	
	printf("ray->x = %f\n", ray_vector->x);
	printf("ray->y = %f	\n", ray_vector->y);
	i = 0.4;
	while (42)
	{
		ray.x = (cub->player_position.x + (i * ray_vector->x));
		ray.y = (cub->player_position.y + (i * ray_vector->y));
		if (cub->map.map_array[(int)ray.y][(int)ray.x] != '0' && cub->map.map_array[(int)ray.y][(int)ray.x] != cub->player_char)
			break ;
		my_mlx_pixel_put(&cub->image, (ray.x * cub->minmap_square), (ray.y) * cub->minmap_square, 0xFF0000);
		i+= 0.1;
	}
}
