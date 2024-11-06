#ifndef CUB_H
#define CUB_H

# include "minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <fcntl.h>//open

#define WIDTH 1240
#define HEIGHT 840

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

typedef struct	s_coordinate {

	double x;
	double y;

}				t_coordinate;

typedef struct	s_ray {

	struct s_cub_data *cub;
	t_coordinate	direction;
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
	int			map_height;
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

typedef struct s_textures {

	void	*textures_xpm[4];
	int		textures_height[4];
	int		textures_width[4];

}				t_textures;

typedef struct		s_cub_data {

	char			**test_map_array; // remover apos o parsing
	void			*mlx_ptr;
	void			*mlx_window;
	char			player_char;
	t_coordinate	*player_position;
	double			player_angle_rad;
	t_coordinate	*player_dir;
	t_coordinate	*plane;
	t_map			*map;
	t_image 		*image;
	t_textures		*textures;
	int 			rotation;
	
}					t_cub_data;

t_cub_data	*init_cub_struct();
void		define_player_vectors(t_cub_data *cub);
void		define_initial_rotation(t_cub_data *cub);
void		define_textures(t_cub_data *cub);


t_ray	*calculate_ray(t_cub_data * cub, int ray_id);
void	calculate_deltas(t_ray *ray);
void	increment_to_next_intersection(t_ray *ray);
void	calculate_wall_distance(t_ray *ray);
void	draw_pixels_in_image(t_ray *ray, t_image *image);
int		ray_casting(t_cub_data *cub);

//move_player.c
void	move_player(int key, t_cub_data *cub);
void	move_player_up(t_cub_data *cub, int quadrant);
void	move_player_down(t_cub_data *cub, int quadrant);
void	move_player_left(t_cub_data *cub, int quadrant);
void	move_player_right(t_cub_data *cub, int quadrant);

int check_quadrant(double player_angle);
void change_player_position(t_coordinate *new_pos, t_cub_data *cub);

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
char	**extract_map(t_cub_data *cub, char **file, int y);
int		empty_line(char *line);
int		map_size_valid_char(char **file, int i);
int		find_player_position(t_cub_data *cub);
int		closed_by_walls(t_cub_data *cub, char **map);
int		find_wall(t_cub_data *cub, char **map, int y, int x);

//frees.c
void	free_matriz(char **str);

#endif