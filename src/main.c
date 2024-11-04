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

t_cub_data *init_cub_struct(void)
{
	t_cub_data *cub;
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1000010001\n100010001\n100000001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');

	cub = ft_calloc(sizeof(t_cub_data), 1);
	if (!cub)
		return (NULL);
	cub->test_map_array = test_map_array; // remover
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	cub->player_position = ft_calloc(sizeof(t_coordinate), 1);
	cub->player_dir = ft_calloc(sizeof(t_coordinate), 1);
	cub->plane = ft_calloc(sizeof(t_coordinate), 1);
	cub->image = ft_calloc(sizeof(t_image), 1);
	cub->image->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->image->addr = mlx_get_data_addr(cub->image->img, &cub->image->bits_per_pixel,
		&cub->image->line_len, &cub->image->endian);
	cub->player_char = 'S'; // ALTERAR PARA DEFINIR AUTOMATICAMENTE APOS O PARSER
	cub->player_angle_rad = PI;
	define_player_vectors(cub);
	cub->rotation = 0;
	if (cub->player_char == 'E')
		cub->rotation = 12;
	if (cub->player_char == 'S')
		cub->rotation = 24;
	if (cub->player_char == 'W')
		cub->rotation = 36;
	return (cub);
}

void	draw_pixels_in_image(t_ray *ray, t_image *image)
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
		my_mlx_pixel_put(image, ray->id, floor, 0xB9BEB9);
	while (++ceiling <= pix_end)
		my_mlx_pixel_put(image, ray->id, ceiling, 0x009FDA);
	while(pix_end >= pix_start)
	{
		if (ray->side_colision == 1)
			my_mlx_pixel_put(image, ray->id, pix_start, 0x009F00);
		else
			my_mlx_pixel_put(image, ray->id, pix_start, 0x00C700);
		pix_start++;
	}
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

int main(void)
{
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1000010001\n100010001\n100000001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');
	t_cub_data *cub;
	
	cub = init_cub_struct();
	
	cub->player_position->x = 5.2;
	cub->player_position->y = 2.7;
	
	//ray_casting(cub, test_map_array);
	//mlx_xpm_file_to_image = // colocar imagem de inicio 
	mlx_hook(cub->mlx_window, 2, (1L<<0), handle_input, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_casting, cub);
	mlx_loop(cub->mlx_ptr);
}
