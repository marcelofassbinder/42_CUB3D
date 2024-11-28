/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:55:37 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/28 20:24:03 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ray_casting(t_cub *cub)
{
	int		ray_id;
	t_ray	*ray;

	ray_id = -1;
	if (!cub->start_game)
		return (0);
	while (++ray_id < WIDTH)
	{
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, cub->image.img, 0, 0);
	return (1);
}

/*
camera_x -> varia de -1 a 1
dir -> define o valor x e y no vetor de direcao de cada raio
map_x -> define o quadrado do mapa onde o player esta
*/
t_ray	*calculate_ray(t_cub *cub, int ray_id)
{
	t_ray	*ray;

	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return (panic(cub, "Malloc failed in ray struct"), NULL);
	ray->cub = cub;
	ray->id = ray_id;
	ray->camera_x = 2 * (ray->id / (double)WIDTH) - 1;
	ray->dir.x = cub->player_dir.x + cub->plane.x * ray->camera_x;
	ray->dir.y = cub->player_dir.y + cub->plane.y * ray->camera_x;
	ray->map_x = (int)cub->player_position.x;
	ray->map_y = (int)cub->player_position.y;
	calculate_deltas(ray);
	return (ray);
}

/*
delta_x -> distance traveled to walk 1 unit in X axis
delta_y -> distance traveled to walk 1 unit in Y axis
if step_x = 1 -> the next step will be to the right
if step_x = -1 -> the next step will be to the left
side_x -> calculate the distance from the player position until the first
	intersection in X axis to the right or left
if step_y = 1 -> the next step will be down
if step_y = -1 -> the next step will be up
side_y -> calculate the distance from the player position until the first
	intersection in Y axis down or up
*/
void	calculate_deltas(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = sqrt(1 + pow((ray->dir.y / ray->dir.x), 2));
	if (ray->dir.y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = sqrt(1 + pow((ray->dir.x / ray->dir.y), 2));
	ray->step_x = 1;
	ray->side_x = (ray->map_x + 1 - ray->cub->player_position.x) * ray->delta_x;
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->cub->player_position.x - ray->map_x) * ray->delta_x;
	}
	ray->step_y = 1;
	ray->side_y = (ray->map_y + 1 - ray->cub->player_position.y) * ray->delta_y;
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->cub->player_position.y - ray->map_y) * ray->delta_y;
	}
}

void	increment_to_next_intersection(t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side_colision = true;
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side_colision = false;
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side_colision == 1)
		ray->wall_distance = (ray->map_x - ray->cub->player_position.x
				+ (1 - ray->step_x) / 2) / ray->dir.x;
	else
		ray->wall_distance = (ray->map_y - ray->cub->player_position.y
				+ (1 - ray->step_y) / 2) / ray->dir.y;
	ray->line_height = (int)(HEIGHT / ray->wall_distance);
}
