/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:58:47 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 14:06:36 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	rotate_player(int key, t_cub *cub)
{
	if (key == ARROW_RIGHT)
		cub->rotation++;
	else if (key == ARROW_LEFT)
		cub->rotation--;
	if (cub->rotation < 0)
		cub->rotation += 48;
	if (cub->rotation == 48)
		cub->rotation = 0;
	cub->player_angle_rad = cub->rotation * (PI/24);
	cub->player_dir->x = sin(cub->player_angle_rad);
	cub->player_dir->y = - cos(cub->player_angle_rad);
	cub->plane->x = cos(cub->player_angle_rad);
	cub->plane->y = sin(cub->player_angle_rad);	
}

int check_quadrant(double player_angle)
{
	if (player_angle >= 0 && player_angle < PI/2)
		return (1);
	else if (player_angle >= PI/2 && player_angle < PI)
		return (2);
	else if (player_angle >= PI && player_angle < 3 * PI / 2)
		return (3);
	else
		return (4);
}

void change_player_position(t_coordinate *new_pos, t_cub *cub)
{
	char possible_new_pos;
	char possible_new_pos_X;
	char possible_new_pos_Y;

	possible_new_pos = cub->map->map_array[(int)new_pos->y][(int)new_pos->x];
	possible_new_pos_X = cub->map->map_array[(int)cub->player_position->y][(int)new_pos->x];
	possible_new_pos_Y = cub->map->map_array[(int)new_pos->y][(int)cub->player_position->x];
	if (possible_new_pos && possible_new_pos != WALL 
		&& possible_new_pos_X != WALL && possible_new_pos_Y != WALL)
	{
		cub->player_position->x = new_pos->x;
		cub->player_position->y = new_pos->y;
	}
}
