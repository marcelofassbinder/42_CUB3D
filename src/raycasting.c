/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:55:37 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/08 16:35:10 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	ray_casting(t_cub *cub)
{
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->image->img, 0, 0);
	return (1);
	//mlx_destroy_image(cub->mlx_ptr, cub->image->img);
}

int	define_texture_orientation(t_ray *ray)
{
	if (ray->side_colision)
	{
		if (ray->direction.x > 0)
			return (1); // E
		else
			return (3);// W
	}
	else
	{
		if (ray->direction.y < 0)
			return (0); // N
		else
			return (2); // S
	}
}

void	draw_textures(t_cub *cub, t_ray *ray)
{
	double	wall_x; // the exact point that wall was hit
	double	step; // how much to increase in y axis inside the texture, every iteration of the loop 
	double	tex_y; // the y coordinate in the texture
	int		tex_x; // the x coordinate in the texture
	int		tex_color;
	int		tex_index;
	
	tex_index = define_texture_orientation(ray);
	if (ray->side_colision)
		wall_x = cub->player_position->y + (ray->wall_distance * ray->direction.y);
	else
		wall_x = cub->player_position->x + (ray->wall_distance * ray->direction.x);
	wall_x -= floor(wall_x);
	tex_x = (int) (wall_x * cub->textures->text_w[tex_index]);
	if ((ray->side_colision && ray->direction.x < 0) || (ray->side_colision == 0 && ray->direction.y > 0))
		tex_x = cub->textures->text_w[tex_index] - tex_x - 1;
	step = 1.0 * cub->textures->text_h[tex_index] / ray->line_height;
	tex_y = (ray->pix_start - HEIGHT / 2 + ray->line_height / 2) * step;
	while(ray->pix_start < ray->pix_end)
	{
		tex_color = get_color_from_pixel(&cub->textures->images[tex_index], tex_x, (int)tex_y);
		my_mlx_pixel_put(cub->image, ray->id, ray->pix_start, tex_color);
		tex_y += step;
		ray->pix_start++;
	}
}

t_ray	*calculate_ray(t_cub * cub, int ray_id)
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
	ray->map_x = (int)cub->player_position->x; // define o quadrado do mapa onde o player esta
	ray->map_y = (int)cub->player_position->y;
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
	ray->side_x = (ray->map_x + 1 - ray->cub->player_position->x) * ray->delta_x; //calculate the distance from the player position until the first intersection in X axis to the right;
	if (ray->direction.x < 0) 
	{
		ray->step_x = -1; // the next step will be to the left;
		ray->side_x = (ray->cub->player_position->x - ray->map_x) * ray->delta_x; // calculate the distance from the player position until the first intersection in X axis to the left;
	}
	ray->step_y = 1; // the next step will be down;
	ray->side_y = (ray->map_y + 1 - ray->cub->player_position->y) * ray->delta_y;// calculate the distance from the player position until the first intersection in Y axis down;
	if (ray->direction.y < 0) 
	{
		ray->step_y = -1; // the next step will be up;
		ray->side_y = (ray->cub->player_position->y - ray->map_y) * ray->delta_y; // calculate the distance from the player position until the first intersection in Y axis up;
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
		ray->wall_distance = (ray->map_x - ray->cub->player_position->x + (1 - ray->step_x) / 2)
			/ ray->direction.x;
	else
		ray->wall_distance = (ray->map_y - ray->cub->player_position->y + (1 - ray->step_y) / 2)
			/ ray->direction.y;
	ray->line_height = (int) (HEIGHT / ray->wall_distance);
}