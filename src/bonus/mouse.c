/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:01:09 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 18:49:43 by mfassbin         ###   ########.fr       */
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
	if (key == LEFT_CLICK && cub->reload == 40 && cub->has_bullet)
	{
		cub->shot = 1;
		cub->has_bullet = false;
	}
	else if (key == RIGHT_CLICK && cub->shot == 0 && !cub->has_bullet)
	{
		cub->reload = 41;
		cub->has_bullet = true;
	}
	else if (key == SCROLL)
	{
		if (cub->fixed_mouse_center == true)
			cub->fixed_mouse_center = false;
		else
			cub->fixed_mouse_center = true;
	}
	return (1);
}
