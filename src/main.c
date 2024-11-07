/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:46 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/07 19:47:53 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	draw_pixels_in_image(t_ray *ray, t_image *image)
{
	int floor;
	int ceiling;

	ray->pix_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (ray->pix_start < 0)
		ray->pix_start = 0;
	ray->pix_end = (HEIGHT / 2) + (ray->line_height / 2);
	if (ray->pix_end >= HEIGHT)
		ray->pix_end = HEIGHT - 1;
	floor = HEIGHT + 1;
	ceiling = -1;
	while (--floor >= ray->pix_start)
		my_mlx_pixel_put(image, ray->id, floor, 0xB9BEB9);
	while (++ceiling <= ray->pix_end)
		my_mlx_pixel_put(image, ray->id, ceiling, 0x009FDA);
	/* while(ray->pix_end >= ray->pix_start)
	{
		if (ray->side_colision == 1)
			my_mlx_pixel_put(image, ray->id, ray->pix_start, 0x009F00);
		else
			my_mlx_pixel_put(image, ray->id, ray->pix_start, 0x00C700);
		ray->pix_start++;
	} */
	//draw_wall_textures(t_ray *ray, t_image *image, int pix_start, int pix_end);
}

void	rotate_player(int key, t_cub_data *cub)
{
	if (key == ARROW_RIGHT)
		cub->rotation++;
	else if (key == ARROW_LEFT)
		cub->rotation--;
	if (cub->rotation < 0)
		cub->rotation += 48;
	if (cub->rotation == 48)
		cub->rotation = 0;
	cub->player_angle_rad = cub->rotation * (PI/24);
	cub->player_dir->x = sin(cub->player_angle_rad);
	cub->player_dir->y = - cos(cub->player_angle_rad);
	cub->plane->x = cos(cub->player_angle_rad);
	cub->plane->y = sin(cub->player_angle_rad);
	
}

int	handle_input(int key, t_cub_data *cub)
{
	if (key == ESC)
		exit(0);
		//close_window()
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_player(key, cub);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT)
		rotate_player(key, cub);
	return (1);
}

int main(int argc, char **argv)
{
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1000010001\n100010001\n100000001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');
	t_cub_data *cub;
	
	cub = init_cub_struct();
	
	/* cub->player_position->x = 5.2;
	cub->player_position->y = 2.7; */
	
	//mlx_xpm_file_to_image = // colocar imagem de inicio 
	
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
			return (printf("Erro no parsing\n"));
		//cub->player_pos_X = 5.2;
		//cub->player_pos_Y = 2.7;

	}
	else
		return (printf("ERROR!\nINVALID INPUT!\n"));
	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting, cub);
	mlx_loop(cub->mlx_ptr);

}
