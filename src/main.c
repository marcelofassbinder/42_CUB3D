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
	cub->test_map_array = test; // remover
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->img = ft_calloc(sizeof(t_image), 1);
	cub->img->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel,
		&cub->img->line_len, &cub->img->endian);
	cub->player_dir = ft_calloc(sizeof(t_vector), 1);
	cub->plane = ft_calloc(sizeof(t_vector), 1);
	cub->player_char = 'N'; // ALTERAR PARA DEFINIR AUTOMATICAMENTE APOS O PARSER
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
	while(pix_end >= pix_start)
	{
		if (ray->side_colision == 1)
			my_mlx_pixel_put(ray->cub->img, ray->id, pix_start, 0x009F00);
		else
			my_mlx_pixel_put(ray->cub->img, ray->id, pix_start, 0x00C700);
		pix_start++;
	}
}

void	rotate_player(int key, t_cub_data *cub)
{
	static int l = 1;

	if (key == ARROW_RIGHT || key == ARROW_LEFT)
	{
		if (key == ARROW_RIGHT)
			l++;
		else
			l--;
		cub->player_dir->x = sin(l * PI/24);
		cub->player_dir->y = - cos(l * PI/24);
		cub->plane->x = cos(l * PI/24);
		cub->plane->y = sin(l * PI/24);
	}
	ray_casting(cub, cub->test_map_array);
}

int	handle_input(int key, t_cub_data *cub)
{
	if (key == ESC)
		exit(0);
		//close_window()
	move_player(key, cub);
	rotate_player(key, cub);
	return (1);
}

int main(void)
{
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');
	t_cub_data *cub;
	
	cub = init_cub_struct(test_map_array);
	
	cub->player_pos_X = 5.2;
	cub->player_pos_Y = 2.7;
	
	ray_casting(cub, test_map_array);

	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop(cub->mlx_ptr);
}
