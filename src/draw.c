/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:02:49 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 14:06:36 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_floor_ceiling(t_cub *cub, t_ray *ray)
{
	int floor;
	int ceiling;

	ray->pix_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (ray->pix_start < 0)
		ray->pix_start = 0;
	ray->pix_end = (HEIGHT / 2) + (ray->line_height / 2);
	if (ray->pix_end >= HEIGHT)
		ray->pix_end = HEIGHT - 1;
	floor = HEIGHT + 1;
	ceiling = -1;
	while (++ceiling <= ray->pix_end)
		my_mlx_pixel_put(cub->image, ray->id, ceiling, cub->map->c_hex);
	while (--floor >= ray->pix_start)
		my_mlx_pixel_put(cub->image, ray->id, floor, cub->map->f_hex);
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
