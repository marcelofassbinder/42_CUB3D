/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:23:21 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 16:27:09 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	ray_casting_bonus(t_cub *cub)
{
	if (!cub->start_game)
		return (0);
	if (cub->fixed_mouse_center == true)
		mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	ray_casting_loop(cub);
	minimap(cub);
	draw_gun(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, cub->image.img, 0, 0);
	return (1);
}

void	ray_casting_loop(t_cub *cub)
{
	int		ray_id;
	t_ray	*ray;

	ray_id = -1;
	while (++ray_id < WIDTH)
	{
		ray = calculate_ray(cub, ray_id);
		while (42)
		{
			increment_to_next_intersection(ray);
			if (cub->map.map_array[ray->map_y][ray->map_x] == WALL
				|| (cub->map.map_array[ray->map_y][ray->map_x] == C_DOOR))
				break ;
		}
		calculate_wall_distance(ray);
		draw_floor_ceiling(cub, ray);
		draw_textures(cub, ray);
		free(ray);
	}
}
