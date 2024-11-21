/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/20 16:40:33 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_bonus.h"

/* int	handle_input_bonus(int key, t_cub *cub)
{
	if (!cub->start_game && key == SPACE)
		cub->start_game = true;
	if (key == ESC)
	{
		panic(cub);
		exit(0);
	}
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(key, cub);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		rotate_player(key, cub);
	return (1);
} */

int	handle_mouse(int key, int x, int y, t_cub *cub)
{
	(void) x;
	(void) y;
	if (key == 1)
	{
		cub->shot = true;
	}
	return (1);
}

void	init_gun(t_cub *cub)
{
	cub->gun.images[0].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun.xpm", &cub->gun.images[0].width, &cub->gun.images[0].height);
	cub->gun.images[0].addr = mlx_get_data_addr(cub->gun.images[0].img, &cub->gun.images[0].bits_per_pixel, &cub->gun.images[0].line_len, &cub->gun.images[0].endian);
	cub->gun.images[1].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun1.xpm", &cub->gun.images[1].width,
			&cub->gun.images[1].height);
	cub->gun.images[1].addr = mlx_get_data_addr(cub->gun.images[1].img, &cub->gun.images[1].bits_per_pixel, &cub->gun.images[1].line_len, &cub->gun.images[1].endian);
	cub->gun.images[2].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun2.xpm", &cub->gun.images[2].width,
			&cub->gun.images[2].height);
	cub->gun.images[2].addr = mlx_get_data_addr(cub->gun.images[2].img, &cub->gun.images[2].bits_per_pixel, &cub->gun.images[2].line_len, &cub->gun.images[2].endian);
	cub->gun.images[3].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun3.xpm", &cub->gun.images[3].width,
			&cub->gun.images[3].height);
	cub->gun.images[3].addr = mlx_get_data_addr(cub->gun.images[3].img, &cub->gun.images[3].bits_per_pixel, &cub->gun.images[3].line_len, &cub->gun.images[3].endian);
	cub->gun.images[4].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun4.xpm", &cub->gun.images[4].width,
			&cub->gun.images[4].height);
	cub->gun.images[4].addr = mlx_get_data_addr(cub->gun.images[4].img, &cub->gun.images[4].bits_per_pixel, &cub->gun.images[4].line_len, &cub->gun.images[4].endian);
	cub->gun.images[5].img = mlx_xpm_file_to_image(cub->mlx_ptr,
		"./textures/gun5.xpm", &cub->gun.images[5].width,
			&cub->gun.images[5].height);
	cub->gun.images[5].addr = mlx_get_data_addr(cub->gun.images[5].img, &cub->gun.images[5].bits_per_pixel, &cub->gun.images[5].line_len, &cub->gun.images[5].endian);
}

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
			return (EXIT_FAILURE);//free_parsing(cub));
		init_window(cub);
		define_textures(cub);
		init_gun(cub);
		render_initial_image(cub);
	}
	else
		return (printf("ERROR!\nINVALID INPUT!\n"));
	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_mouse_hook(cub->mlx_window, handle_mouse, cub);
	mlx_loop(cub->mlx_ptr);
} 