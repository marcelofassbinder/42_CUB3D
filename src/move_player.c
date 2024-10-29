/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:54:50 by mfassbin          #+#    #+#             */
/*   Updated: 2024/10/29 19:59:04 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	move_player(int key, t_cub_data *cub)
{
	/* if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
	{
		if (!check_quadrant(cub))	
			return ;
		ray_casting(cub, cub->test_map_array);
	} */
	if (key == KEY_W)
	{
		if (!move_player_up(cub))
			return ;
	}
	else if (key == KEY_A)
	{
		if (!move_player_left(cub))
			return ;
	}
	else if (key == KEY_S)
	{
		if (!move_player_down(cub))
			return ;
	}
	else if (key == KEY_D)
	{
		if (!move_player_right(cub))
			return ;
	}
	ray_casting(cub, cub->test_map_array);
}

/* double	move_in_x(t_cub_data *cub, double angle, int quadrant)
{
	if (quadrant == 2 || quadrant == 3)
		return () 
}

int check_quadrant(t_cub_data *cub)
{
	double angle;
	double new_pos_X;
	double new_pos_Y;

	if (cub->player_angle_rad >= 0 && cub->player_angle_rad < PI/2)
		angle = cub->player_angle_rad;
	else if (cub->player_angle_rad >= PI/2 && cub->player_angle_rad < PI)
		angle = cub->player_angle_rad - PI / 2;
	else if (cub->player_angle_rad >= PI && cub->player_angle_rad < 3 * PI / 2)
		angle = (3 * PI / 2) - cub->player_angle_rad;
	else if (cub->player_angle_rad >= 3 * PI / 2 && cub->player_angle_rad < 2 * PI)
		angle = (2 * PI) - cub->player_angle_rad;
	new_pos_X += MOVE_SPEED * sin(cub->player_angle_rad);
	new_pos_Y -= MOVE_SPEED * cos(cub->player_angle_rad);
} */

int	move_player_up(t_cub_data *cub)
{
	double 	new_pos_X;
	double 	new_pos_Y;
	char	new_map_position;

	new_pos_X = cub->player_pos_X;
	new_pos_Y = cub->player_pos_Y;
	printf("player angle = %f\n", cub->player_angle_rad);
	if (cub->player_angle_rad >= 0 && cub->player_angle_rad < PI/2)
	{
		new_pos_X += MOVE_SPEED * sin(cub->player_angle_rad);
		new_pos_Y -= MOVE_SPEED * cos(cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= PI/2 && cub->player_angle_rad < PI)
	{
		new_pos_X += MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
		new_pos_Y += MOVE_SPEED * sin(cub->player_angle_rad - PI / 2);
	}
	if (cub->player_angle_rad >= PI && cub->player_angle_rad < 3 * PI / 2)
	{
		new_pos_X -= MOVE_SPEED * cos((3 * PI / 2) - cub->player_angle_rad);
		new_pos_Y += MOVE_SPEED * sin((3 * PI / 2) - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= 3 * PI / 2 && cub->player_angle_rad < 2 * PI)
	{
		new_pos_X -= MOVE_SPEED * sin((2 * PI) - cub->player_angle_rad);
		new_pos_Y -= MOVE_SPEED * cos((2 * PI) - cub->player_angle_rad);
	}
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
	printf("player angle = %f\n", cub->player_angle_rad);
	if (cub->player_angle_rad >= 0 && cub->player_angle_rad < PI/2)
	{
		new_pos_X -= MOVE_SPEED * sin(cub->player_angle_rad);
		new_pos_Y += MOVE_SPEED * cos(cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= PI/2 && cub->player_angle_rad < PI)
	{
		new_pos_X -= MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
		new_pos_Y -= MOVE_SPEED * sin(cub->player_angle_rad - PI / 2);
	}
	if (cub->player_angle_rad >= PI && cub->player_angle_rad < 3 * PI / 2)
	{
		new_pos_X += MOVE_SPEED * cos((3 * PI / 2) - cub->player_angle_rad);
		new_pos_Y -= MOVE_SPEED * sin((3 * PI / 2) - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= 3 * PI / 2 && cub->player_angle_rad < 2 * PI)
	{
		new_pos_X += MOVE_SPEED * sin((2 * PI) - cub->player_angle_rad);
		new_pos_Y += MOVE_SPEED * cos((2 * PI) - cub->player_angle_rad);
	}
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
	if (cub->player_angle_rad >= 0 && cub->player_angle_rad < PI / 2)
	{
		printf("1o QUADRANTE\n");
		new_pos_X -= MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos_Y -= MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= PI/2 && cub->player_angle_rad < PI)
	{
		printf("2o QUADRANTE\n");
		new_pos_X += MOVE_SPEED * sin(cub->player_angle_rad - PI / 2 );
		new_pos_Y -= MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
	}
	if (cub->player_angle_rad >= PI && cub->player_angle_rad < 3 * PI / 2)
	{
		printf("3o QUADRANTE\n");
		new_pos_X -= MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos_Y -= MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= 3 * PI / 2 && cub->player_angle_rad < 2 * PI)
	{
		printf("4o QUADRANTE\n");
		new_pos_X -= MOVE_SPEED * sin(cub->player_angle_rad - (3 * PI / 2));
		new_pos_Y += MOVE_SPEED * cos(cub->player_angle_rad - (3 * PI / 2));
	}
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
	if (cub->player_angle_rad >= 0 && cub->player_angle_rad < PI / 2)
	{
		printf("1o QUADRANTE\n");
		new_pos_X += MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos_Y += MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= PI/2 && cub->player_angle_rad < PI)
	{
		printf("2o QUADRANTE\n");
		new_pos_X -= MOVE_SPEED * sin(cub->player_angle_rad - PI / 2 );
		new_pos_Y += MOVE_SPEED * cos(cub->player_angle_rad - PI / 2);
	}
	if (cub->player_angle_rad >= PI && cub->player_angle_rad < 3 * PI / 2)
	{
		printf("3o QUADRANTE\n");
		new_pos_X += MOVE_SPEED * sin(PI / 2 - cub->player_angle_rad);
		new_pos_Y += MOVE_SPEED * cos(PI / 2 - cub->player_angle_rad);
	}
	if (cub->player_angle_rad >= 3 * PI / 2 && cub->player_angle_rad < 2 * PI)
	{
		printf("4o QUADRANTE\n");
		new_pos_X += MOVE_SPEED * sin(cub->player_angle_rad - (3 * PI / 2));
		new_pos_Y -= MOVE_SPEED * cos(cub->player_angle_rad - (3 * PI / 2));
	}
	new_map_position = cub->test_map_array[(int)new_pos_Y][(int)new_pos_X];
	if (new_map_position && new_map_position != WALL)
	{
		cub->player_pos_Y = new_pos_Y;
		cub->player_pos_X = new_pos_X;
		return (1);
	}
	return (0);
}
