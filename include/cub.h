#ifndef CUB_H
#define CUB_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
#include <fcntl.h>//open

#define WIDTH 840
#define HEIGHT 620

#define KEY_W XK_w
#define KEY_A XK_a
#define KEY_S XK_s
#define KEY_D XK_d
#define ESC XK_Escape

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
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*ceiling;
	int			c_rgb[3];
	int			c_hex;
	char		*floor;
	int			f_rgb[3];
	int			f_hex;
}				t_map;

typedef struct	s_cub_data {
	
	char		**test_map_array; // remover apos o parsing
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

t_cub_data	*init_cub_struct(char **test);
void		define_player_vectors(t_cub_data *cub);
t_ray	*calculate_ray(t_cub_data * cub, int ray_id);
void	calculate_deltas(t_ray *ray);
void	increment_to_next_intersection(t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	draw_pixels_in_image(t_ray *ray);
void	ray_casting(t_cub_data *cub, char **map);

//utils.c
void 	my_mlx_pixel_put(t_image *img, int x, int y, int color);
char	*ft_strstr(char *str, char *to_find);

//parsing/parsing.c
int		find_extension(char *map, char *ext);
int		parsing(t_cub_data *cub, char *argv);
char	**get_matrix_from_file(t_cub_data *cub, char *file);
int		count_lines(char *file);

//parsing/texture.c
int		init_texture_color(t_cub_data *cub);
char	*get_info(char *file, int flag);
int		is_valid_textures(t_cub_data *cub);
int		duplicate_texture_or_color(t_cub_data *cub);
int		is_valid_colors(t_cub_data *cub);

//parsing/color.c
int		has_three_numbers(char *str);
int		ft_isdigit_space_tab(int c);
void	save_rgb(t_cub_data *cub);
int		rgb_to_hex(int rgb[3]);

//parsing/map.c
char	**extract_map(char **file, int i);
int		map_size_valid_char(char **file, int i);
int		find_player_position(t_cub_data *cub);
int		closed_by_walls(char **map);
int		find_wall(char **map, int y, int x);

//frees.c
void	free_matriz(char **str);

#endif