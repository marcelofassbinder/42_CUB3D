/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:55:37 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/05 19:39:58 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ray_casting(t_cub_data *cub, char **map)
{
	int ray_id = -1;
	while (++ray_id < WIDTH)
	{
		t_ray *ray;

		ray = calculate_ray(cub, ray_id);
		while (42) 
		{
			increment_to_next_intersection(ray);
			if (map[ray->map_y][ray->map_x] == '1')
				break ;
		}
		calculate_wall_distance(ray);
		draw_pixels_in_image(ray);
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->img->img, 0, 0);
}

t_ray	*calculate_ray(t_cub_data * cub, int ray_id)
{
	t_ray *ray;

	ray = ft_calloc(sizeof(t_ray), 1);
	if (!ray)
		return (NULL);
	ray->cub = cub;
	ray->id = ray_id;
	ray->camera_x = 2 * (ray->id / (double)WIDTH) - 1; // camera_x varia de -1 a 1
	ray->direction.x = cub->player_dir->x + cub->plane->x * ray->camera_x; // define o valor de x no vetor de direcao de cada raio
	ray->direction.y = cub->player_dir->y + cub->plane->y * ray->camera_x; // define o valor de y no vetor de direcao de cada raio
	ray->map_x = (int)cub->player_pos_X; // define o quadrado do mapa onde o player esta
	ray->map_y = (int)cub->player_pos_Y;
	calculate_deltas(ray);
	return (ray);
}

void	calculate_deltas(t_ray *ray)
{
	if (ray->direction.x == 0)
		ray->delta_x= 1e30;
	else
		ray->delta_x = sqrt(1 + pow((ray->direction.y/ray->direction.x), 2)); // distance traveled to walk 1 unit in X axis;
	if (ray->direction.y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = sqrt(1 + pow((ray->direction.x/ray->direction.y), 2)); // ditance traveled to walk 1 unit in Y axis;
	ray->step_x = 1; // the next step will be to the right;
	ray->side_x = (ray->map_x + 1 - ray->cub->player_pos_X) * ray->delta_x; //calculate the distance from the player position until the first intersection in X axis to the right;
	if (ray->direction.x < 0) 
	{
		ray->step_x = -1; // the next step will be to the left;
		ray->side_x = (ray->cub->player_pos_X - ray->map_x) * ray->delta_x; // calculate the distance from the player position until the first intersection in X axis to the left;
	}
	ray->step_y = 1; // the next step will be down;
	ray->side_y = (ray->map_y + 1 - ray->cub->player_pos_Y) * ray->delta_y;// calculate the distance from the player position until the first intersection in Y axis down;
	if (ray->direction.y < 0) 
	{
		ray->step_y = -1; // the next step will be up;
		ray->side_y = (ray->cub->player_pos_Y - ray->map_y) * ray->delta_y; // calculate the distance from the player position until the first intersection in Y axis up;
	}
}

void	increment_to_next_intersection(t_ray *ray)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		ray->map_x += ray->step_x;
		ray->side_colision = true; // cruza linha verical
	}
	else
	{
		ray->side_y += ray->delta_y;
		ray->map_y += ray->step_y;
		ray->side_colision = false; //cruza linha horizontal
	}
}

void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side_colision == 1)
		ray->wall_distance = (ray->map_x - ray->cub->player_pos_X + (1 - ray->step_x) / 2)
			/ ray->direction.x;
	else
		ray->wall_distance = (ray->map_y - ray->cub->player_pos_Y + (1 - ray->step_y) / 2)
			/ ray->direction.y;
	ray->line_height = (int) (HEIGHT / ray->wall_distance);
}