/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:22:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/23 14:33:21 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	handle_input(int key, t_cub *cub)
{
	if (!cub->start_game && key == SPACE)
		cub->start_game = true;
	if (key == ESC)
	{
		panic(cub);
		exit(0);
	}
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(key, cub);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		rotate_player(key, cub);
	return (1);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;
	int 	offset;
	
	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

unsigned int get_color_from_pixel(t_image *img, int x, int y)
{
	char	*dst;
	int 	offset;

	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	return(*(unsigned int *)dst);
}

/**
 * @brief Finds the first occurrence of the substring `to_find` in the string `str`, 
 * ignoring leading spaces and tabs in `str`. 
 *
 * @return A pointer to the first occurrence of `to_find` in `str`, 
 * or NULL if `to_find` is not found.
 */
char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(to_find);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], to_find, len))
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void resize_image(t_image *src, t_image *dst, int new_width, int new_height)
{
    int		x;
	int		y;
    int 	src_x;
	int		src_y;
	int		color;
    double	scale_x;
    double	scale_y;
	
	scale_x = (double)src->width / new_width;
	scale_y = (double)src->height / new_height;
	y = -1;
    while (++y < new_height)
    {
		x = -1;
        while (++x < new_width)
        {
            src_x = (int)(x * scale_x);
            src_y = (int)(y * scale_y);
            color = get_color_from_pixel(src, src_x, src_y);
            my_mlx_pixel_put(dst, x, y, color);
        }
    }
}
void	init_image_xpm(t_cub *cub, t_image *i, char *path)
{
	i->img = mlx_xpm_file_to_image(cub->mlx_ptr, path, &i->width, &i->height);
	if (!i->img)
		return(error_message("Image creation failed!"), panic(cub));
	i->addr = mlx_get_data_addr(i->img, &i->bits_per_pixel, &i->line_len, &i->endian);
}

void	init_new_image(t_cub *cub, t_image *image, int width, int height)
{
	image->img = mlx_new_image(cub->mlx_ptr, width, height);
	if (!image->img)
		return (error_message("Image creation failed!"), panic(cub));
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_len, &image->endian);
	image->width = width;
	image->height = height;
}

void render_initial_image(t_cub *cub)
{
    t_image resized;

	init_image_xpm(cub, &cub->initial, "./textures/initial.xpm");
  	init_new_image(cub, &resized, WIDTH, HEIGHT);
    resize_image(&cub->initial, &resized, WIDTH, HEIGHT);
    mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window,resized.img, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, cub->initial.img);
	cub->initial = resized;
}
