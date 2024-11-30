/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/30 16:01:23 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_struct();
	if (argc == 2 && find_extension(argv[1], ".cub"))
	{
		parsing(cub, argv[1]);
		init_mlx(cub);
		init_textures(cub);
		init_gun(cub);
		draw_initial_image(cub);
	}
	else
		return (panic(cub, "Invalid input!"), EXIT_FAILURE);
	mlx_hook(cub->mlx_win, 2, 1L << 0, handle_input_bonus, cub);
	mlx_hook(cub->mlx_win, 17, 1L << 2, close_window, cub);
	mlx_hook(cub->mlx_win, 6, PointerMotionMask, handle_mouse_move, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_mouse_hook(cub->mlx_win, handle_mouse, cub);
	mlx_loop(cub->mlx_ptr);
}
