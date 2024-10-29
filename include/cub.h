#ifndef CUB_H
#define CUB_H

# include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <fcntl.h>//open

#define WIDTH 840
#define HEIGHT 620

// KEY DEFINES
#define KEY_W XK_w
#define KEY_A XK_a
#define KEY_S XK_s
#define KEY_D XK_d
#define ARROW_LEFT XK_Left
#define ARROW_RIGHT XK_Right
#define ESC XK_Escape

#define WALL '1'
#define MOVE_SPEED 0.1111111
#define ROTATION_SPEED 0.25

#define PI 3.14159265358979323846

typedef struct	s_vector {

	double x;
	double y;
}				t_vector;

typedef struct	s_ray {

	struct s_cub_data *cub;
	t_vector	direction;
	double		camera_x;
	double 		delta_x;
	double 		delta_y;
	double 		side_x;
	double 		side_y;
	double		wall_distance;
	int 		id;
	int 		map_x;
	int 		map_y;
	int 		step_x;
	int 		step_y;
	int			line_height;
	bool		side_colision;

}				t_ray;

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
	
	char		**test_map_array; // remover apos o parsing
	void		*mlx_ptr;
	void		*mlx_window;
	t_image 	*img;
	char		player_char;
	double		player_pos_X;
	double		player_pos_Y;
	double		player_angle_rad;
	t_vector	*player_dir;
	t_vector	*plane;
	t_map		*map;
	
}				t_cub_data;

t_cub_data	*init_cub_struct(char **test);
void		define_player_vectors(t_cub_data *cub);
t_ray	*calculate_ray(t_cub_data * cub, int ray_id);
void	calculate_deltas(t_ray *ray);
void	increment_to_next_intersection(t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	draw_pixels_in_image(t_ray *ray);
void	ray_casting(t_cub_data *cub, char **test_map_array);

//move_player.c
void	move_player(int key, t_cub_data *cub);
int		move_player_up(t_cub_data *cub);
int		move_player_down(t_cub_data *cub);
int		move_player_left(t_cub_data *cub);
int		move_player_right(t_cub_data *cub);

//utils.c
void my_mlx_pixel_put(t_image *img, int x, int y, int color);

//parsing/parsing.c
int		find_extension(char *map, char *ext);
void	parsing(t_cub_data *cub, char *argv);
char	**get_matrix_from_file(t_cub_data *cub, char *file);
int		count_lines(char *file);

//parsing/map.c

#endif