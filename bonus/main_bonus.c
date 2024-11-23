/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:40:05 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/23 14:59:45 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_bonus.h"


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

void	init_gun(t_cub *cub)
{
	init_image_xpm(cub, &cub->gun.images[0], "./textures/gun1.xpm");
	init_image_xpm(cub, &cub->gun.images[1], "./textures/gun2.xpm");
	init_image_xpm(cub, &cub->gun.images[2], "./textures/gun3.xpm");
	init_image_xpm(cub, &cub->gun.images[3], "./textures/gun4.xpm");
	init_image_xpm(cub, &cub->gun.images[4], "./textures/gun5.xpm");
	init_image_xpm(cub, &cub->gun.images[5], "./textures/r1.xpm");
	init_image_xpm(cub, &cub->gun.images[6], "./textures/r2.xpm");
	init_image_xpm(cub, &cub->gun.images[7], "./textures/r3.xpm");
	init_image_xpm(cub, &cub->gun.images[8], "./textures/r4.xpm");
	init_image_xpm(cub, &cub->gun.images[9], "./textures/r5.xpm");
	init_image_xpm(cub, &cub->gun.images[10], "./textures/r6.xpm");
	init_image_xpm(cub, &cub->gun.images[11], "./textures/r7.xpm");
	init_image_xpm(cub, &cub->gun.images[12], "./textures/r8.xpm");
	init_image_xpm(cub, &cub->gun.images[13], "./textures/r9.xpm");
	init_image_xpm(cub, &cub->gun.images[14], "./textures/r10.xpm");
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
