/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:54:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 14:06:36 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	move_player(int key, t_cub *cub)
{
	int quadrant;
	
	quadrant = check_quadrant(cub->player_angle_rad);
	if (key == KEY_W)
		return (move_player_up(cub, quadrant));
	else if (key == KEY_A)
		return (move_player_left(cub, quadrant));
	else if (key == KEY_S)
		return (move_player_down(cub, quadrant));
	else if (key == KEY_D)
		return (move_player_right(cub, quadrant));
}

void	move_player_up(t_cub *cub, int quadrant)
{
	t_coordinate	new_pos;

	new_pos.x = cub->player_position->x;
	new_pos.y = cub->player_position->y;
	if (quadrant == 1)
	{
		new_pos.x += MOVE_SPEED * sin(cub->player_angle_rad);
		new_pos.y -= MOVE_SPEED * cos(cub->player_angle_rad);
	}
	if (quadrant == 2)
	{
		new_pos.x += MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
		new_pos.y += MOVE_SPEED * sin(cub->player_angle_rad - PI / 2);
	}
	if (quadrant == 3)
	{
		new_pos.x -= MOVE_SPEED * cos((3 * PI / 2) - cub->player_angle_rad);
		new_pos.y += MOVE_SPEED * sin((3 * PI / 2) - cub->player_angle_rad);
	}
	if (quadrant == 4)
	{
		new_pos.x -= MOVE_SPEED * sin((2 * PI) - cub->player_angle_rad);
		new_pos.y -= MOVE_SPEED * cos((2 * PI) - cub->player_angle_rad);
	}
	return (change_player_position(&new_pos, cub));
}

void	move_player_down(t_cub *cub, int quadrant)
{
	t_coordinate	new_pos;

	new_pos.x = cub->player_position->x;
	new_pos.y = cub->player_position->y;
	if (quadrant == 1)
	{
		new_pos.x -= MOVE_SPEED * sin(cub->player_angle_rad);
		new_pos.y += MOVE_SPEED * cos(cub->player_angle_rad);
	}
	if (quadrant == 2)
	{
		new_pos.x -= MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
		new_pos.y -= MOVE_SPEED * sin(cub->player_angle_rad - PI / 2);
	}
	if (quadrant == 3)
	{
		new_pos.x += MOVE_SPEED * cos((3 * PI / 2) - cub->player_angle_rad);
		new_pos.y -= MOVE_SPEED * sin((3 * PI / 2) - cub->player_angle_rad);
	}
	if (quadrant == 4)
	{
		new_pos.x += MOVE_SPEED * sin((2 * PI) - cub->player_angle_rad);
		new_pos.y += MOVE_SPEED * cos((2 * PI) - cub->player_angle_rad);
	}
	return (change_player_position(&new_pos, cub));
}

void	move_player_left(t_cub *cub, int quadrant)
{
	t_coordinate	new_pos;

	new_pos.x = cub->player_position->x;
	new_pos.y = cub->player_position->y;
	if (quadrant == 1)
	{
		new_pos.x -= MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos.y -= MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (quadrant == 2)
	{
		new_pos.x += MOVE_SPEED * sin(cub->player_angle_rad - PI / 2 );
		new_pos.y -= MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
	}
	if (quadrant == 3)
	{
		new_pos.x -= MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos.y -= MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (quadrant == 4)
	{
		new_pos.x -= MOVE_SPEED * sin(cub->player_angle_rad - (3 * PI / 2));
		new_pos.y += MOVE_SPEED * cos(cub->player_angle_rad - (3 * PI / 2));
	}
	return (change_player_position(&new_pos, cub));
}

void	move_player_right(t_cub *cub, int quadrant)
{
	t_coordinate	new_pos;

	new_pos.x = cub->player_position->x;
	new_pos.y = cub->player_position->y;
	if (quadrant == 1)
	{
		new_pos.x += MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos.y += MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (quadrant == 2)
	{
		new_pos.x -= MOVE_SPEED * sin(cub->player_angle_rad - PI / 2 );
		new_pos.y += MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
	}
	if (quadrant == 3)
	{
		new_pos.x += MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos.y += MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (quadrant == 4)
	{
		new_pos.x += MOVE_SPEED * sin(cub->player_angle_rad - (3 * PI / 2));
		new_pos.y -= MOVE_SPEED * cos(cub->player_angle_rad - (3 * PI / 2));
	}
	return (change_player_position(&new_pos, cub));
}
