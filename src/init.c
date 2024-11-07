/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfassbin <mfassbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:57:54 by mfassbin          #+#    #+#             */
/*   Updated: 2024/11/07 17:24:56 by mfassbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_cub_data *init_cub_struct(void)
{
	t_cub_data *cub;
	/* char test_map[100] = "1111111111\n1111100001\n10000N0001\n1000010001\n100010001\n100000001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n'); */

	cub = ft_calloc(sizeof(t_cub_data), 1);
	if (!cub)
		return (NULL);
	//cub->test_map_array = test_map_array; // remover
	cub->map = ft_calloc(sizeof(t_map), 1);
	//cub->map->map_array = test_map_array;
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->player_position = ft_calloc(sizeof(t_coordinate), 1);
	cub->player_dir = ft_calloc(sizeof(t_coordinate), 1);
	cub->plane = ft_calloc(sizeof(t_coordinate), 1);
	cub->image = ft_calloc(sizeof(t_image), 1);
	cub->image->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image->addr = mlx_get_data_addr(cub->image->img, &cub->image->bits_per_pixel,
		&cub->image->line_len, &cub->image->endian);
	//cub->player_char = 'S'; // ALTERAR PARA DEFINIR AUTOMATICAMENTE APOS O PARSER
	/* define_player_vectors(cub);
	define_initial_rotation(cub); */

	return (cub);
}

void	define_initial_rotation(t_cub_data *cub)
{
	if (cub->player_char == 'N')
	{
		cub->player_angle_rad = 0;
		cub->rotation = 0;
	}
	if (cub->player_char == 'E')
	{
		cub->player_angle_rad = PI / 2;
		cub->rotation = 12;
	}
	if (cub->player_char == 'S')
	{
		cub->player_angle_rad = PI;
		cub->rotation = 24;
	}
	if (cub->player_char == 'W')
	{	
		cub->player_angle_rad = 3 * PI / 2;
		cub->rotation = 36;
	}
}

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
			cub->player_dir->y = 1;
			cub->plane->x = -1;
		}
	}
	else if (cub->player_char == 'W' || cub->player_char == 'E')
	{
		cub->plane->x = 0;
		cub->plane->y = -1;
		cub->player_dir->x = -1;
		cub->player_dir->y = 0;
		if (cub->player_char == 'E')
		{
			cub->player_dir->x = 1;
			cub->plane->y = 1;
		}
	}
}

void	define_textures(t_cub_data *cub)
{
	t_textures *textures;

	textures = ft_calloc(sizeof(t_textures), 1);
	
	textures->images[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->map->north, &textures->textures_width[0], &textures->textures_height[0]);
	textures->images[0].addr = mlx_get_data_addr(textures->images[0].img, 
		&textures->images[0].bits_per_pixel, &textures->images[0].line_len, &textures->images[0].endian);
	textures->images[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->map->east, &textures->textures_width[1], &textures->textures_height[1]);
	textures->images[1].addr = mlx_get_data_addr(textures->images[1].img, 
		&textures->images[1].bits_per_pixel, &textures->images[1].line_len, &textures->images[1].endian);
	textures->images[2].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->map->south, &textures->textures_width[2], &textures->textures_height[2]);
	textures->images[2].addr = mlx_get_data_addr(textures->images[2].img,
		&textures->images[2].bits_per_pixel, &textures->images[2].line_len, &textures->images[2].endian);
	textures->images[3].img = mlx_xpm_file_to_image(cub->mlx_ptr, 
		cub->map->north, &textures->textures_width[3], &textures->textures_height[3]);
	textures->images[3].addr = mlx_get_data_addr(textures->images[3].img, 
		&textures->images[3].bits_per_pixel, &textures->images[3].line_len, &textures->images[3].endian);
	cub->textures = textures;
}
