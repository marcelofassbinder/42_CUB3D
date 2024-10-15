#include "../include/cub.h"

int main(void)
{
	t_cub_data cub;
	
	cub.mlx_ptr = mlx_init();
	cub.mlx_window = mlx_new_window(cub.mlx_ptr, 500, 500, "cub3d");
	mlx_loop(cub.mlx_ptr);
}