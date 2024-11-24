/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/24 20:53:16 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub_bonus.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	cub = init_cub_struct();
	cub->map.fd = open(argv[1], O_RDONLY);
	if (cub->map.fd < 0)
	{
		free(cub);
		return (printf("ERROR!\nfd < 0!\n"));
	}
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
		return (printf("ERROR!\nINVALID INPUT!\n"));
	mlx_hook(cub->mlx_win, 2, (1L << 0), handle_input, cub);
	mlx_hook(cub->mlx_win, 6, PointerMotionMask, handle_mouse_move, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting_bonus, cub);
	mlx_mouse_hook(cub->mlx_win, handle_mouse, cub);
	mlx_loop(cub->mlx_ptr);
}

int	handle_mouse_move(int x, int y, t_cub *cub)
{
	(void)y;
	if (x - 3 > cub->mouse_x)
	{
		cub->rotation++;
		cub->mouse_x = x + 3;
	}
	if (x + 3 < cub->mouse_x)
	{
		cub->rotation--;
		cub->mouse_x = x - 3;
	}
	if (cub->rotation < 0)
		cub->rotation += 48;
	if (cub->rotation == 48)
		cub->rotation = 0;
	cub->player_angle_rad = cub->rotation * (PI / 24);
	cub->player_dir.x = sin(cub->player_angle_rad);
	cub->player_dir.y = -cos(cub->player_angle_rad);
	cub->plane.x = cos(cub->player_angle_rad) * 0.66;
	cub->plane.y = sin(cub->player_angle_rad) * 0.66;
	return (0);
}

int	handle_mouse(int key, int x, int y, t_cub *cub)
{
	(void) x;
	(void) y;
	if (key == 1)
	{
		if (cub->reload == 50 && cub->has_bullet)
		{
			cub->shot = 1;
			cub->has_bullet = false;
		}
	}
	else if (key == 3)
	{
		if (cub->shot == 0 && !cub->has_bullet)
		{
			cub->reload = 51;
			cub->has_bullet = true;
		}
	}
	return (1);
}
