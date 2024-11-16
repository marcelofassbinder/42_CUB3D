/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/16 22:11:11 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_bonus.h"

int main(int argc, char **argv)
{
	t_cub *cub;
	
	cub = init_cub_struct();
	initial_image(cub);
	cub->map->fd = open(argv[1], O_RDONLY);//fecha no parsing
	if (cub->map->fd < 0)
	{
		free(cub->map);
		free(cub);
		return (printf("ERROR!\nfd < 0!\n"));
	}
	//ate aqui pra checagem de input
	if (argc == 2 && find_extension(argv[1], ".cub") && cub->map->fd > 0)
	{
		if (parsing(cub, argv[1]))
			return (EXIT_FAILURE);//free_parsing(cub));
		//cub->player_pos_X = 5.2;
		//cub->player_pos_Y = 2.7;

	}
	else
		return (printf("ERROR!\nINVALID INPUT!\n"));
	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_loop(cub->mlx_ptr);
}