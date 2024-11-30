/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/30 19:00:45 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_struct();
	if (argc == 2 && find_extension(argv[1], ".cub"))
	{
		cub->is_bonus = true;
		parsing(cub, argv[1]);
		init_mlx(cub);
		init_textures(cub);
		init_gun(cub);
		draw_initial_image(cub);
	}
	else
		return (panic(cub, "Invalid input!"), EXIT_FAILURE);
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, handle_input_bonus, cub);
	mlx_hook(cub->mlx_win, DestroyNotify, ButtonPressMask, close_window, cub);
	mlx_hook(cub->mlx_win, MotionNotify, PointerMotionMask,
		handle_mouse_move, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_mouse_hook(cub->mlx_win, handle_mouse, cub);
	mlx_loop(cub->mlx_ptr);
}
