/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:46 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/28 20:27:30 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_struct();
	if (argc == 2 && find_extension(argv[1], ".cub"))
	{
		parsing(cub, argv[1]);
		init_mlx(cub);
		init_textures(cub);
		draw_initial_image(cub);
	}
	else
		return (panic(cub, "Invalid input!"), EXIT_FAILURE);
	mlx_hook(cub->mlx_win, 2, 1L << 0, handle_input, cub);
	mlx_hook(cub->mlx_win, 17, 1L << 2, close_window, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting, cub);
	mlx_loop(cub->mlx_ptr);
}
