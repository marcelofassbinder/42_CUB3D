/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:54:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/10/28 17:58:41 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	move_player(int key, t_cub_data *cub)
{
	if (key == KEY_W)
	{
		if (!move_player_up(cub))
			return ;
	}
	else if (key == KEY_S)
	{
		if (!move_player_down(cub))
			return ;
	}
	else if (key == KEY_A)
	{
		if (!move_player_left(cub))
			return ;
	}
	else if (key == KEY_D)
	{
		if (!move_player_right(cub))
			return ;
	}
	ray_casting(cub, cub->test_map_array);
}

int	move_player_up(t_cub_data *cub)
{
	double 	new_pos_X;
	double 	new_pos_Y;
	char	new_map_position;

	new_pos_X = cub->player_pos_X;
	new_pos_Y = cub->player_pos_Y;
	if (cub->player_char == 'N')
		new_pos_Y -= MOVE_SPEED;
	if (cub->player_char == 'S')
		new_pos_Y += MOVE_SPEED;
	if (cub->player_char == 'W')
		new_pos_X -= MOVE_SPEED;
	if (cub->player_char == 'E')
		new_pos_X += MOVE_SPEED;
	new_map_position = cub->test_map_array[(int)new_pos_Y][(int)new_pos_X];
	if (new_map_position && new_map_position != WALL)
	{
		cub->player_pos_Y = new_pos_Y;
		cub->player_pos_X = new_pos_X;
		return (1);
	}
	return (0);
}

int	move_player_down(t_cub_data *cub)
{
	double 	new_pos_X;
	double 	new_pos_Y;
	char	new_map_position;

	new_pos_X = cub->player_pos_X;
	new_pos_Y = cub->player_pos_Y;
	if (cub->player_char == 'N')
		new_pos_Y += MOVE_SPEED;
	if (cub->player_char == 'S')
		new_pos_Y -= MOVE_SPEED;
	if (cub->player_char == 'W')
		new_pos_X += MOVE_SPEED;
	if (cub->player_char == 'E')
		new_pos_X -= MOVE_SPEED;
	new_map_position = cub->test_map_array[(int)new_pos_Y][(int)new_pos_X];
	if (new_map_position && new_map_position != WALL)
	{
		cub->player_pos_Y = new_pos_Y;
		cub->player_pos_X = new_pos_X;
		return (1);
	}
	return (0);
}

int	move_player_left(t_cub_data *cub)
{
	double 	new_pos_X;
	double 	new_pos_Y;
	char	new_map_position;

	new_pos_X = cub->player_pos_X;
	new_pos_Y = cub->player_pos_Y;
	if (cub->player_char == 'N')
		new_pos_X -= MOVE_SPEED;
	if (cub->player_char == 'S')
		new_pos_X += MOVE_SPEED;
	if (cub->player_char == 'W')
		new_pos_Y += MOVE_SPEED;
	if (cub->player_char == 'E')
		new_pos_Y -= MOVE_SPEED;
	new_map_position = cub->test_map_array[(int)new_pos_Y][(int)new_pos_X];
	if (new_map_position && new_map_position != WALL)
	{
		cub->player_pos_Y = new_pos_Y;
		cub->player_pos_X = new_pos_X;
		return (1);
	}
	return (0);
}

int	move_player_right(t_cub_data *cub)
{
	double 	new_pos_X;
	double 	new_pos_Y;
	char	new_map_position;

	new_pos_X = cub->player_pos_X;
	new_pos_Y = cub->player_pos_Y;
	if (cub->player_char == 'N')
		new_pos_X += MOVE_SPEED;
	if (cub->player_char == 'S')
		new_pos_X -= MOVE_SPEED;
	if (cub->player_char == 'W')
		new_pos_Y -= MOVE_SPEED;
	if (cub->player_char == 'E')
		new_pos_Y += MOVE_SPEED;
	new_map_position = cub->test_map_array[(int)new_pos_Y][(int)new_pos_X];
	if (new_map_position && new_map_position != WALL)
	{
		cub->player_pos_Y = new_pos_Y;
		cub->player_pos_X = new_pos_X;
		return (1);
	}
	return (0);
}
