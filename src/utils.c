/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:22:14 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/29 17:59:47 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	error_message(char *str)
{
	write(STDERR_FILENO, "Error!\n", 7);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

char	next_position_char(t_cub *cub)
{
	int 			quadrant;
	char 			c;
	t_coordinate	player;

	player = cub->player_position;
	quadrant = check_quadrant(cub->player_angle_rad);
	c = 0;
	if (quadrant == 1)
	{
		if (player.x > player.y)
		{
			if (cub->map.map_array[(int)player.y][(int)player.x + 1])
				c = cub->map.map_array[(int)player.y][(int)player.x + 1];
		}
		else if (player.x <= player.y)
			if (cub->map.map_array[(int)player.y - 1][(int)player.x])
				c = cub->map.map_array[(int)player.y - 1][(int)player.x];
	}
	else if (quadrant == 2)
	{
		if (player.x > player.y)
		{
			if (cub->map.map_array[(int)player.y][(int)player.x + 1])
				c = cub->map.map_array[(int)player.y][(int)player.x + 1];
		}
		else if (player.x <= player.y)
			if (cub->map.map_array[(int)player.y + 1][(int)player.x])
				c = cub->map.map_array[(int)player.y + 1][(int)player.x];
	}
	else if (quadrant == 3)
	{
		if (player.x < player.y)
		{
			if (cub->map.map_array[(int)player.y][(int)player.x - 1])
				c = cub->map.map_array[(int)player.y][(int)player.x - 1];
		}
		else if (player.x >= player.y)
			if (cub->map.map_array[(int)player.y + 1][(int)player.x])
				c = cub->map.map_array[(int)player.y + 1][(int)player.x];
	}
	else if (quadrant == 4)
	{
		if (player.x < player.y)
		{
			if (cub->map.map_array[(int)player.y][(int)player.x - 1])
				c = cub->map.map_array[(int)player.y][(int)player.x - 1];
		}
		else if (player.x >= player.y)
			if (cub->map.map_array[(int)player.y - 1][(int)player.x])
				c = cub->map.map_array[(int)player.y - 1][(int)player.x];
	}
	return (c);
}

int	handle_input(int key, t_cub *cub)
{
	if (key == SPACE)
	{
		printf("next char is %c\n", next_position_char(cub));
		if (!cub->start_game)
			cub->start_game = true;
		else
		{
			if (!cub->door_is_open && next_position_char(cub) == DOOR)
				cub->door_is_open = true;
			else if (cub->door_is_open && next_position_char(cub) == DOOR)
				cub->door_is_open = false;
		}
	}
	if (key == ESC)
		close_window(cub);
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(key, cub);
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
		rotate_player(key, cub);
	return (1);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	*(unsigned int *)dst = color;
}

unsigned int	get_color_from_pixel(t_image *img, int x, int y)
{
	char	*dst;
	int		offset;

	offset = (y * img->line_len + x * (img->bits_per_pixel / 8));
	dst = img->addr + offset;
	return (*(unsigned int *)dst);
}

/**
 * @brief Finds the first occurrence of the substring `to_find` in the
 * string `str`, 
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
