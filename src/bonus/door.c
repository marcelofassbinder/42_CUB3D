/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:57:34 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 16:06:33 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

bool	is_door(int y, int x, t_cub *cub)
{
	char **map;

	map = cub->map.map_array;
	if (map[y][x] && (map[y][x] == C_DOOR
		|| map[y][x] == O_DOOR))
		return (true);
	return (false);
}

t_coordinate	*is_close_to_door(t_cub *cub)
{
	t_coordinate	pos;
	char			**map;
	
	map = cub->map.map_array;
	pos.x = cub->player_position.x;
	pos.y = cub->player_position.y;
	if (is_door((int)pos.y, (int)(pos.x + 1), cub))
		return (&(t_coordinate){pos.x + 1,pos.y});
	if (is_door((int)(pos.y - 1), (int)(pos.x + 1), cub))
		return (&(t_coordinate){pos.x + 1,pos.y - 1});
	if (is_door((int)(pos.y + 1), (int)(pos.x + 1), cub))
		return (&(t_coordinate){pos.x + 1,pos.y + 1});
	if (is_door((int)(pos.y), (int)(pos.x - 1), cub))
		return (&(t_coordinate){pos.x - 1,pos.y});
	if (is_door((int)(pos.y - 1), (int)(pos.x - 1), cub))
		return (&(t_coordinate){pos.x - 1,pos.y - 1});
	if (is_door((int)(pos.y + 1), (int)(pos.x - 1), cub))
		return (&(t_coordinate){pos.x - 1,pos.y + 1});
	if (is_door((int)(pos.y + 1), (int)(pos.x), cub))
		return (&(t_coordinate){pos.x,pos.y + 1});
	if (is_door((int)(pos.y - 1), (int)(pos.x), cub))
		return (&(t_coordinate){pos.x,pos.y - 1});
	return (NULL);
}

int	handle_input_bonus(int key, t_cub *cub)
{
	t_coordinate	*pos;
	
	pos = is_close_to_door(cub);
	if (key == SPACE)
	{
		if (!cub->start_game)
			cub->start_game = true;
		else if (cub->start_game && pos)
		{
			if (cub->map.map_array[(int)pos->y][(int)pos->x] == O_DOOR)
				cub->map.map_array[(int)pos->y][(int)pos->x] = C_DOOR;
			else
				cub->map.map_array[(int)pos->y][(int)pos->x] = O_DOOR;
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
