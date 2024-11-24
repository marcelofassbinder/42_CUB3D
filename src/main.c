/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:46 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/23 15:21:30 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int main(int argc, char **argv)
{
	t_cub *cub;
	
	cub = init_cub_struct();
	cub->map.fd = open(argv[1], O_RDONLY);//fecha no parsing
	if (cub->map.fd < 0)
	{
		free(cub);
		return (printf("ERROR!\nfd < 0!\n"));
	}
	//ate aqui pra checagem de input
	if (argc == 2 && find_extension(argv[1], ".cub") && cub->map.fd > 0)
	{
		if (parsing(cub, argv[1]))
			return (EXIT_FAILURE);
		init_mlx(cub);
		init_textures(cub);
		draw_initial_image(cub);
	}
	else
		return (printf("ERROR!\nINVALID INPUT!\n"));
	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting, cub);
	mlx_loop(cub->mlx_ptr);

}

