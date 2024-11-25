/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:58:47 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/25 20:42:53 by mfassbin         ###   ########.fr       */
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
		cub->rotation += 96;
	if (cub->rotation == 96)
		cub->rotation = 0;
	cub->player_angle_rad = cub->rotation * (PI / 48);
	cub->player_dir.x = sin(cub->player_angle_rad);
	cub->player_dir.y = -cos(cub->player_angle_rad);
	cub->plane.x = cos(cub->player_angle_rad) * 0.66;
	cub->plane.y = sin(cub->player_angle_rad) * 0.66;
}

int	check_quadrant(double player_angle)
{
	if (player_angle >= 0 && player_angle < PI / 2)
		return (1);
	else if (player_angle >= PI / 2 && player_angle < PI)
		return (2);
	else if (player_angle >= PI && player_angle < 3 * PI / 2)
		return (3);
	else
		return (4);
}

void	change_player_position(t_coordinate *new_pos, t_cub *cub)
{
	char	possible_new_pos;
	char	possible_new_pos_x;
	char	possible_new_pos_y;

	possible_new_pos = cub->map.map_array[(int)new_pos->y][(int)new_pos->x];
	possible_new_pos_x = cub->map.map_array[(int)cub
		->player_position.y][(int)new_pos->x];
	possible_new_pos_y = cub->map.map_array[(int)new_pos
		->y][(int)cub->player_position.x];
	if (possible_new_pos && possible_new_pos != WALL
		&& possible_new_pos_x != WALL && possible_new_pos_y != WALL)
	{
		cub->player_position.x = new_pos->x;
		cub->player_position.y = new_pos->y;
		walk_move(cub);
	}
}

void	walk_move(t_cub *cub)
{
	static int old_walk = 5;

	if (cub->walk <= old_walk && cub->walk <= 5)
		cub->walk ++;
	else if (cub->walk >= old_walk && cub->walk >= 0)
		cub->walk --;
	if (cub->walk == 5)
		old_walk = 0;
	if (cub->walk == 0)
		old_walk = 5;
}
