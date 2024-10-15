#ifndef CUB_H
#define CUB_H

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_position {

	int x;
	int y;
}				t_position;

typedef struct	s_map {

	char 		**map_array;
	t_position	player_position;

}				t_map;

typedef struct	s_cub_data {
	
	void *mlx_ptr;
	void *mlx_window;
	t_map *map;
	
}				t_cub_data;


#endif