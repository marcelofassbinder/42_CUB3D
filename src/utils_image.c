/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 19:59:10 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/24 20:26:38 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	resize_image(t_image *src, t_image *dst, int new_width, int new_height)
{
	t_coordinate	scale;
	t_coordinate	source;
	int				x;
	int				y;
	int				color;

	scale.x = (double)src->width / new_width;
	scale.y = (double)src->height / new_height;
	y = -1;
	while (++y < new_height)
	{
		x = -1;
		while (++x < new_width)
		{
			source.x = (int)(x * scale.x);
			source.y = (int)(y * scale.y);
			color = get_color_from_pixel(src, (int)source.x, (int)source.y);
			my_mlx_pixel_put(dst, x, y, color);
		}
	}
}

void	init_image_xpm(t_cub *cub, t_image *i, char *path)
{
	i->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &i->width, &i->height);
	if (!i->img)
		return (error_message("Image creation failed!"), panic(cub));
	i->addr = mlx_get_data_addr(i->img, &i->bits_per_pixel,
			&i->line_len, &i->endian);
}

void	init_new_image(t_cub *cub, t_image *image, int width, int height)
{
	image->img = mlx_new_image(cub->mlx_ptr, width, height);
	if (!image->img)
		return (error_message("Image creation failed!"), panic(cub));
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_len, &image->endian);
	image->width = width;
	image->height = height;
}

void	draw_initial_image(t_cub *cub)
{
	t_image	resized;

	init_image_xpm(cub, &cub->initial, "./textures/initial.xpm");
	init_new_image(cub, &resized, WIDTH, HEIGHT);
	resize_image(&cub->initial, &resized, WIDTH, HEIGHT);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, resized.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->initial.img);
	cub->initial = resized;
}
