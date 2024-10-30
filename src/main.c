/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:46 by ismirand          #+#    #+#             */
/*   Updated: 2024/10/30 12:56:13 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	define_player_vectors(t_cub_data *cub)
{
	if (cub->player_char == 'N' || cub->player_char == 'S')
	{
		cub->plane->x = 1;
		cub->plane->y = 0;
		cub->player_dir->x = 0;
		cub->player_dir->y = -1;
		if (cub->player_char == 'S')
		{
			cub->player_dir->x = 0;
			cub->player_dir->y = 1;
		}
	}
	else if (cub->player_char == 'W' || cub->player_char == 'E') 
	{
		cub->plane->x = 0;
		cub->plane->y = 1;
		cub->player_dir->x = -1;
		cub->player_dir->y = 0;
		if (cub->player_char == 'E')
		{
			cub->player_dir->x = 1;
			cub->player_dir->y = 0;
		}
	}
}

t_cub_data *init_cub_struct(char **test)
{
	t_cub_data *cub;
	
	cub = ft_calloc(sizeof(t_cub_data), 1);
	if (!cub)
		return (NULL);
	cub->map = ft_calloc(sizeof(t_map), 1);
	cub->test_map_array = test; // remover
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->img = ft_calloc(sizeof(t_image), 1);
	cub->img->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
		&cub->img->line_len, &cub->img->endian);
	cub->player_dir = ft_calloc(sizeof(t_vector), 1);
	cub->plane = ft_calloc(sizeof(t_vector), 1);
	cub->player_char = 'W'; // ALTERAR PARA DEFINIR AUTOMATICAMENTE APOS O PARSER
	define_player_vectors(cub);
	return (cub);
}

void	draw_pixels_in_image(t_ray *ray)
{
	int pix_start;
	int pix_end;
	int floor;
	int ceiling;

	pix_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (pix_start < 0)
		pix_start = 0;
	pix_end = (HEIGHT / 2) + (ray->line_height / 2);
	if (pix_end >= HEIGHT)
		pix_end = HEIGHT - 1;
	floor = HEIGHT + 1;
	ceiling = -1;
	while (--floor >= pix_start)
		my_mlx_pixel_put(ray->cub->img, ray->id, floor, 0xB9BEB9);
	while (++ceiling <= pix_end)
		my_mlx_pixel_put(ray->cub->img, ray->id, ceiling, 0x009FDA);
	while(pix_end >= pix_start) {
		if (ray->side_colision == 1)
			my_mlx_pixel_put(ray->cub->img, ray->id, pix_start, 0x009F00);
		else
			my_mlx_pixel_put(ray->cub->img, ray->id, pix_start, 0x00C700);
		pix_start++;
	}
}

void	move_player(int key, t_cub_data *cub)
{
	if (key == KEY_W)
	{
		if (cub->player_char == 'N')
			cub->player_pos_Y -= 0.1;
		else if (cub->player_char == 'S')
			cub->player_pos_Y += 0.1;
		else if (cub->player_char == 'E')
			cub->player_pos_X += 0.1;
		else if (cub->player_char == 'W')
			cub->player_pos_X -= 0.1;
		if (cub->test_map_array[(int)cub->player_pos_Y][(int)cub->player_pos_X] == '1')
			return ;
		ray_casting(cub, cub->test_map_array);
	}
}

int	handle_input(int key, t_cub_data *cub)
{
	//printf("\nthe key %i has been pressed\n", key);
	if (key == ESC)
		exit(0);
		//close_window()
	move_player(key, cub);
	//rotate_player(key, cub);
	return (1);
}

int main(int argc, char **argv)
{
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');
	t_cub_data *cub;
	
	cub = init_cub_struct(test_map_array);

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
		cub->player_pos_X = 5.2;
		cub->player_pos_Y = 2.7;
		
		ray_casting(cub, test_map_array);
	
		mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
		mlx_loop(cub->mlx_ptr);
	}
	else
		return (printf("ERROR!\nINVALID INPUT!\n"));

}
