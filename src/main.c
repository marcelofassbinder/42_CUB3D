#include "../include/cub.h"

int main(void)
{
	char test_map[100] = "1111111111\n1111100001\n10000N0001\n1111111111\n";
	char **test_map_array = ft_split(test_map, '\n');
	t_cub_data *cub = ft_calloc(sizeof(t_cub_data), 1);

	int i = 0;
	cub->mlx_ptr = mlx_init();
	cub->mlx_window = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	
	cub->img = ft_calloc(sizeof(t_image), 1);
	cub->img->img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bits_per_pixel, &cub->img->line_len, &cub->img->endian);

	cub->player_pos_X = 5.2;
	cub->player_pos_Y = 2.7;
	
	//printf("%s", test_map);
	cub->player_dir = ft_calloc(sizeof(t_vector), 1);
	cub->player_dir->x = 0;
	cub->player_dir->y = -1;

	cub->plane = ft_calloc(sizeof(t_vector), 1);
	cub->plane->x = 1;
	cub->plane->y = 0;

	if (cub->player_char == 'N') 
	{
		cub->player_dir->x = 0;
		cub->player_dir->y = -1;
		cub->plane->x = 1;
		cub->plane->y = 0;
	}
	else if (cub->player_char == 'S') 
	{
		cub->player_dir->x = 0;
		cub->player_dir->y = 1;
		cub->plane->x = 1;
		cub->plane->y = 0;
	}
	else if (cub->player_char == 'W') 
	{
		cub->player_dir->x = -1;
		cub->player_dir->y = 0;
		cub->plane->x = 0;
		cub->plane->y = 1;
	}
	else if (cub->player_char == 'E') 
	{
		cub->player_dir->x = 1;
		cub->player_dir->y = 0;
		cub->plane->x = 0;
		cub->plane->y = -1;
	}

	double camera_x;
	t_vector ray_dir;
	int mapX;
	int mapY;
	
	double deltaX;
	double deltaY;

	int stepX;
	int stepY;

	double sideX;
	double sideY;

	int side_colision;

	int x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * (x / (double)WIDTH) - 1; // camera_x varia de -1 a 1
		ray_dir.x = cub->player_dir->x + cub->plane->x * camera_x; // define o valor de x no vetor de direcao de cada raio
		ray_dir.y = cub->player_dir->y + cub->plane->y * camera_x; // define o valor de y no vetor de direcao cada raio
		//printf("cam_x = %f\n", camera_x);
		/* printf("\n****** RAIO %i ******\n", x);
		printf("%i", x);
		printf("ray_x = %f\n", ray_dir.x);
		printf("ray_y = %f\n", ray_dir.y); */
		mapX = (int)cub->player_pos_X; // define o quadrado do mapa onde o player esta
		mapY = (int)cub->player_pos_Y;

		if (ray_dir.x == 0)
			deltaX = 1e30;
		else
			deltaX = sqrt(1 + pow((ray_dir.y/ray_dir.x), 2)); // distance traveled to walk 1 unit in X axis;
			//deltaX = fabs(1 / ray_dir.x); //assim da certo mas nao sei o pq
		if (ray_dir.y == 0)
			deltaY = 1e30;
		else
			deltaY = sqrt(1 + pow((ray_dir.x/ray_dir.y), 2)); // ditance traveled to walk 1 unit in Y axis;
			//deltaY = fabs(1 / ray_dir.y);
		/* printf("deltaX = %f\n", deltaX);
		printf("deltaY = %f\n", deltaY); */
		if (ray_dir.x < 0) 
		{
			stepX = -1; // the next step will be to the left;
			sideX = (cub->player_pos_X - mapX) * deltaX; // calculate the distance from the player position until the first intersection in X axis to the left;
		}
		else
		{
			stepX = 1; // the next step will be to the right;
			sideX = (mapX + 1 - cub->player_pos_X) * deltaX; //calculate the distance from the player position until the first intersection in X axis to the right;
			/* printf("entrou e o result eh %f\n", sideX);
			printf("entrou e o mapx eh %d\n", mapX);
			printf("entrou e o PLAYER_x eh %f\n", cub->player_pos_X);
			printf("entrou e o deltaX eh %f\n", deltaX); */
		}
		if (ray_dir.y < 0) 
		{
			stepY = -1; // the next step will be up;
			sideY = (cub->player_pos_Y - mapY) * deltaY; // calculate the distance from the player position until the first intersection in Y axis up;
		}
		else
		{
			stepY = 1; // the next step will be down;
			sideY = (mapY + 1 - cub->player_pos_Y) * deltaY;// calculate the distance from the player position until the first intersection in Y axis down;
		}
		/* printf("deltaX = %f\n", deltaX);
		printf("playerPosX = %f\n", cub->player_pos_X);
		printf("mapX = %d\n", mapX);
		printf("sideX = %f\n", sideX);
		printf("deltaY = %f\n", deltaY);
		printf("sideY = %f\n", sideY);
		printf("mapY = %d\n", mapY);
		printf("playerPosY = %f\n", cub->player_pos_Y); */
		while (42) 
		{
			if (sideX < sideY)
			{
				sideX += deltaX;
				mapX += stepX;
				side_colision = 1; // cruza linha verical
			}
			else
			{
				sideY += deltaY;
				mapY += stepY;
				side_colision = 0; //cruza linha horizontal
			}
			/* printf("new sideX = %f\n", sideX);
			printf("new sideY = %f\n", sideY);
			printf("side colision = %i\n", side_colision); */
			if (test_map_array[mapY][mapX] == '1')
				break ;			
		}
		//calculate the wall height based on the ray distance to the wall;
		double wall_distance;
		int line_height;
		int pixel_draw_start = 0;
		int pixel_draw_end = 0;

		if (side_colision == 1){
			wall_distance = (mapX - cub->player_pos_X + (1 - stepX) / 2) / ray_dir.x;
			/* printf("\nstepX = %i\n", stepX);
			printf("\nray_dir_X = %f\n", ray_dir.x); */
			//wall_distance = sideX - deltaX;
		}
		else {
			wall_distance = (mapY - cub->player_pos_Y + (1 - stepY) / 2) / ray_dir.y;
			/* printf("\nstepY = %i\n", stepY);
			printf("\nray_dir_Y = %f\n", ray_dir.y); */
			//wall_distance = sideY - deltaY;
		}
		line_height = (int) (HEIGHT / wall_distance);

		pixel_draw_start = (HEIGHT / 2) - (line_height / 2);
		if (pixel_draw_start < 0)
			pixel_draw_start = 0;
		pixel_draw_end = (HEIGHT / 2) + (line_height / 2);
		if (pixel_draw_end >= HEIGHT)
			pixel_draw_end = HEIGHT - 1;
		/* printf("wall distance = %f\n", wall_distance);
		printf("pixel start = %i\n", pixel_draw_start);
		printf("pixel end = %i\n", pixel_draw_end); */
		int floor = HEIGHT;
		int ceiling = 0;
		while (floor >= pixel_draw_start) {
			my_mlx_pixel_put(cub->img, x, floor, 0xB9BEB9);
			floor --;
		}
		while (ceiling <= pixel_draw_end) {
			my_mlx_pixel_put(cub->img, x, ceiling, 0x009FDA);
			ceiling++;
		}
		while(pixel_draw_end >= pixel_draw_start) {
			if (side_colision == 1)
				my_mlx_pixel_put(cub->img, x, pixel_draw_start, 0x009F00);
			else
				my_mlx_pixel_put(cub->img, x, pixel_draw_start, 0x00C700);
			//mlx_pixel_put(cub->mlx_ptr, cub->mlx_window, x, pixel_draw_start, 0x0000FF00);
			pixel_draw_start++;
		}
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_window, cub->img->img, 0, 0);
	mlx_loop(cub->mlx_ptr);
}
