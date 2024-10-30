/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:54:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/10/30 18:37:23 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	move_player(int key, t_cub_data *cub)
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

void change_player_position(t_coordinate *new_pos, t_cub_data *cub)
{
	char possible_new_pos;
	char possible_new_pos_X;
	char possible_new_pos_Y;

	possible_new_pos = cub->test_map_array[(int)new_pos->y][(int)new_pos->x];
	possible_new_pos_X = cub->test_map_array[(int)cub->player_position->y][(int)new_pos->x];
	possible_new_pos_X = cub->test_map_array[(int)new_pos->y][(int)cub->player_position->x];
	if (possible_new_pos && possible_new_pos != WALL 
		&& possible_new_pos_X != WALL && possible_new_pos_Y != WALL)
	{
		cub->player_position->x = new_pos->x;
		cub->player_position->y = new_pos->y;
		ray_casting(cub, cub->test_map_array);
	}
}
void	move_player_up(t_cub_data *cub, int quadrant)
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

void	move_player_down(t_cub_data *cub, int quadrant)
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

void	move_player_left(t_cub_data *cub, int quadrant)
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

void	move_player_right(t_cub_data *cub, int quadrant)
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
