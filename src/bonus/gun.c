/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:59:10 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/24 17:18:09 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

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
	draw_gun(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->image.img, 0, 0);
	return (1);
}

void	init_gun(t_cub *cub)
{
	init_image_xpm(cub, &cub->gun[0], "./textures/gun1.xpm");
	init_image_xpm(cub, &cub->gun[1], "./textures/gun2.xpm");
	init_image_xpm(cub, &cub->gun[2], "./textures/gun3.xpm");
	init_image_xpm(cub, &cub->gun[3], "./textures/gun4.xpm");
	init_image_xpm(cub, &cub->gun[4], "./textures/gun5.xpm");
	init_image_xpm(cub, &cub->gun[5], "./textures/r1.xpm");
	init_image_xpm(cub, &cub->gun[6], "./textures/r2.xpm");
	init_image_xpm(cub, &cub->gun[7], "./textures/r3.xpm");
	init_image_xpm(cub, &cub->gun[8], "./textures/r4.xpm");
	init_image_xpm(cub, &cub->gun[9], "./textures/r5.xpm");
	init_image_xpm(cub, &cub->gun[10], "./textures/r6.xpm");
	init_image_xpm(cub, &cub->gun[11], "./textures/r7.xpm");
	init_image_xpm(cub, &cub->gun[12], "./textures/r8.xpm");
	init_image_xpm(cub, &cub->gun[13], "./textures/r9.xpm");
	init_image_xpm(cub, &cub->gun[14], "./textures/r10.xpm");
	//init_image_xpm(cub, &cub->door[0], "./textures/door.xpm");
}

t_image *define_gun_sprite(t_cub *cub)
{
	t_image	*sprite;

	sprite = &cub->gun[0];
	if (cub->reload == 50)
		sprite = &cub->gun[cub->shot / 5];
	else if (cub->shot == 0)
		sprite = &cub->gun[cub->reload / 8];
	if (cub->shot != 0)
		cub->shot ++;
	if (cub->shot == 25)
		cub->shot = 0;
	if (cub->shot == 0 && cub->reload != 50)
		cub->reload ++;
	if (cub->reload == 120)
		cub->reload = 50;
	return (sprite);
}

void	draw_gun(t_cub *cub)
{
	t_image *gun_sprite;
	t_image resized_gun;
	int		gun_x;
	int		gun_y;
	int		color;
	
	gun_sprite = define_gun_sprite(cub);
	init_new_image(cub, &resized_gun, WIDTH / 5, HEIGHT/ 2.5);
	resize_image(gun_sprite, &resized_gun, WIDTH / 5, HEIGHT/ 2.5);
	gun_x = -1;
	while (++gun_x < resized_gun.width)
	{
		gun_y = -1;
		while (++gun_y < resized_gun.height)
		{
			color = get_color_from_pixel(&resized_gun, gun_x, gun_y);
			if ((color & 0xFF000000) != 0x00000000)
				continue ;
			my_mlx_pixel_put(&cub->image, WIDTH/2 + gun_x, gun_y + (HEIGHT - HEIGHT / 2.5), color);
		}
	}
	mlx_destroy_image(cub->mlx_ptr, resized_gun.img);
}
