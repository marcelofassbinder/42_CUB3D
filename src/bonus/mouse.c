/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:01:09 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 16:02:52 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	handle_mouse_move(int x, int y, t_cub *cub)
{
	(void)y;
	if (x > cub->mouse_x)
	{
		cub->mouse_x = x;
		rotate_player(ARROW_RIGHT, cub);
	}
	if (x < cub->mouse_x)
	{
		cub->mouse_x = x;
		rotate_player(ARROW_LEFT, cub);
	}
	return (0);
}

int	handle_mouse(int key, int x, int y, t_cub *cub)
{
	(void) x;
	(void) y;
	if (key == 1 && cub->reload == 40 && cub->has_bullet)
	{
		cub->shot = 1;
		cub->has_bullet = false;
	}
	else if (key == 3 && cub->shot == 0 && !cub->has_bullet)
	{
		cub->reload = 41;
		cub->has_bullet = true;
	}
	else if (key == 2)
	{
		if (cub->fixed_mouse_center == true)
			cub->fixed_mouse_center = false;
		else
			cub->fixed_mouse_center = true;
	}
	return (1);
}
