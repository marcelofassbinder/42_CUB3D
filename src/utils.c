/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:22:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 22:10:21 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	handle_input(int key, t_cub *cub)
{
	if (!cub->start_game && key == SPACE)
	{
		printf("entrou\n");
		cub->start_game = true;
	}
	if (key == ESC)
	{
		free_all_allocated_memory(cub);
		exit(0);
	}
		//close_window()
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
	return(*(unsigned int*)dst);
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
    int x, y;
    int src_x, src_y;
    double scale_x = (double)src->width / new_width;
    double scale_y = (double)src->height / new_height;

    for (y = 0; y < new_height; y++)
    {
        for (x = 0; x < new_width; x++)
        {
            src_x = (int)(x * scale_x);
            src_y = (int)(y * scale_y);
            int color = get_color_from_pixel(src, src_x, src_y);
            my_mlx_pixel_put(dst, x, y, color);
        }
    }
}

void initial_image(t_cub *cub)
{
    t_image *initial;
    t_image *resized;
    int w, h;

    initial = ft_calloc(sizeof(t_image), 1);
    if (!initial)
        return ;
    initial->img = mlx_xpm_file_to_image(cub->mlx_ptr, "./textures/initial.xpm", &w, &h);
    initial->addr = mlx_get_data_addr(initial->img, &initial->bits_per_pixel, &initial->line_len, &initial->endian);
    initial->width = w;
    initial->height = h;

    resized = ft_calloc(sizeof(t_image), 1);
    if (!resized)
        return ;
    resized->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
    resized->addr = mlx_get_data_addr(resized->img, &resized->bits_per_pixel, &resized->line_len, &resized->endian);
    resized->width = WIDTH;
    resized->height = HEIGHT;

    resize_image(initial, resized, WIDTH, HEIGHT);
    mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, resized->img, 0, 0);
    mlx_destroy_image(cub->mlx_ptr, initial->img);
    free(initial);
}
