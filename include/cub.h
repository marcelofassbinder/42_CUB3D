#ifndef CUB_H
#define CUB_H

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 840
#define HEIGHT 620

typedef struct	s_vector {

	double x;
	double y;
}				t_vector;

typedef struct	s_map {

	char 		**map_array;
}				t_map;

typedef struct	s_cub_data {
	
	void *mlx_ptr;
	void *mlx_window;
	char player_char;
	double player_pos_X;
	double player_pos_Y;
	t_vector *player_dir;
	t_vector *plane;
	t_map *map;
	
}				t_cub_data;


#endif