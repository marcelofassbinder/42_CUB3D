/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/28 18:31:44 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_struct();
	cub->map.fd = open(argv[1], O_RDONLY);
	if (cub->map.fd < 0)
		return (error_message("Invalid file!"), panic(cub), 1);
	if (argc == 2 && find_extension(argv[1], ".cub") && cub->map.fd > 0)
	{
		if (parsing(cub, argv[1]))
			return (EXIT_FAILURE);
		init_mlx(cub);
		init_textures(cub);
		init_gun(cub);
		draw_initial_image(cub);
	}
	else
		return (error_message("Invalid input!"), panic(cub), 1);
	mlx_hook(cub->mlx_win, 2, 1L << 0, handle_input, cub);
	mlx_hook(cub->mlx_win, 17, 1L << 2, close_window, cub);
	mlx_hook(cub->mlx_win, 6, PointerMotionMask, handle_mouse_move, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_mouse_hook(cub->mlx_win, handle_mouse, cub);
	mlx_loop(cub->mlx_ptr);
}

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
	if (key == 1)
	{
		if (cub->reload == 40 && cub->has_bullet)
		{
			cub->shot = 1;
			cub->has_bullet = false;
		}
	}
	else if (key == 3)
	{
		if (cub->shot == 0 && !cub->has_bullet)
		{
			cub->reload = 41;
			cub->has_bullet = true;
		}
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
