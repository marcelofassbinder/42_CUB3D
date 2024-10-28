#ifndef CUB_H
#define CUB_H

#include "minilibx-linux/mlx.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>//open
#include <stdbool.h>

#define WIDTH 840
#define HEIGHT 620

typedef struct	s_vector {

	double x;
	double y;
}				t_vector;

typedef struct	s_image {

	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int 		line_len;
	int 		endian;
}				t_image;

typedef struct	s_map {
	char		**file;
	char 		**map_array;
	int			fd;
}				t_map;

typedef struct	s_cub_data {
	
	void		*mlx_ptr;
	void		*mlx_window;
	t_image 	*img;
	char		player_char;
	double		player_pos_X;
	double		player_pos_Y;
	t_vector	*player_dir;
	t_vector	*plane;
	t_map		*map;
	
}				t_cub_data;

//utils.c
void my_mlx_pixel_put(t_image *img, int x, int y, int color);

//parsing/parsing.c
int		find_extension(char *map, char *ext);
void	parsing(t_cub_data *cub, char *argv);
char	**get_matrix_from_file(t_cub_data *cub, char *file);
int		count_lines(char *file);

//parsing/map.c

#endif