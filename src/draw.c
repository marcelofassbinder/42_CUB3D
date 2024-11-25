/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 14:02:49 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/25 20:04:15 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_floor_ceiling(t_cub *cub, t_ray *ray)
{
	int	floor;
	int	ceiling;

	ray->pix_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (ray->pix_start < 0)
		ray->pix_start = 0;
	ray->pix_end = (HEIGHT / 2) + (ray->line_height / 2);
	if (ray->pix_end >= HEIGHT)
		ray->pix_end = HEIGHT - 1;
	floor = HEIGHT + 1;
	ceiling = -1;
	while (++ceiling <= ray->pix_end)
		my_mlx_pixel_put(&cub->image, ray->id, ceiling, cub->map.c_hex);
	while (--floor >= ray->pix_start)
		my_mlx_pixel_put(&cub->image, ray->id, floor, cub->map.f_hex);
}

/* @return
0 -> N
1 -> E
2 -> S
3 -> W
*/
int	define_texture_orientation(t_cub *cub, t_ray *ray)
{
	if (cub->map.map_array[ray->map_y][ray->map_x] == 'D')
		return (4);
	if (ray->side_colision)
	{
		if (ray->dir.x > 0)
			return (1);
		else
			return (3);
	}
	else
	{
		if (ray->dir.y < 0)
			return (0);
		else
			return (2);
	}
}

/*
 wall_x -> the exact point that the wall was hit
 step -> how much to increase in y axis inside the texture,
 	every iteration of the loop
 tex_y -> the y coordinate in the texture
 tex_x -> the x coordinate in the texture
 */
void	draw_textures(t_cub *cub, t_ray *ray)
{
	t_coordinate	tex;
	double			wall_x;
	double			step;
	int				tex_color;
	int				tex_index;

	tex_index = define_texture_orientation(cub, ray);
	if (ray->side_colision)
		wall_x = cub->player_position.y + (ray->wall_distance * ray->dir.y);
	else
		wall_x = cub->player_position.x + (ray->wall_distance * ray->dir.x);
	wall_x -= floor(wall_x);
	tex.x = (int)(wall_x * cub->textures.images[tex_index].width);
	if ((ray->side_colision && ray->dir.x < 0) || (ray->side_colision == 0
			&& ray->dir.y > 0))
		tex.x = cub->textures.images[tex_index].width - (int)tex.x - 1;
	step = 1.0 * cub->textures.images[tex_index].height / ray->line_height;
	tex.y = (ray->pix_start - HEIGHT / 2 + ray->line_height / 2) * step;
	while (ray->pix_start < ray->pix_end)
	{
		tex_color = get_color_from_pixel(&cub->textures.images[tex_index],
				(int)tex.x, (int)tex.y);
		my_mlx_pixel_put(&cub->image, ray->id, ray->pix_start++, tex_color);
		tex.y += step;
	}
}
