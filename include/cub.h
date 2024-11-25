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
#define SPACE XK_space

#define WALL '1'
#define MOVE_SPEED 0.1111111
#define ROTATION_SPEED 0.25

#define PI 3.14159265358979323846

typedef struct			s_coordinate {

	double 				x;
	double 				y;

}						t_coordinate;

typedef struct			s_ray {

	struct s_cub		*cub;
	t_coordinate		direction;
	double				camera_x;
	double 				delta_x;
	double 				delta_y;
	double 				side_x;
	double 				side_y;
	double				wall_distance;
	int 				id;
	int					pix_start;
	int					pix_end;
	int 				map_x;
	int 				map_y;
	int 				step_x;
	int 				step_y;
	int					line_height;
	bool				side_colision;

}						t_ray;

typedef struct			s_image {

	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int 				line_len;
	int 				endian;
	int 				width;
	int 				height;

}						t_image;

typedef struct			s_map {

	struct s_cub		*cub;
	char				**file;
	char 				**map_array;
	int					fd;
	int					map_height;
	char				*ceiling;
	char				*floor;
	int					c_rgb[3];
	int					c_hex;
	int					f_rgb[3];
	int					f_hex;
}						t_map;

typedef struct 			s_text {

	char 				*files[5];
	t_image				images[5];

}						t_text;

typedef struct			s_cub {

	void				*mlx_ptr;
	void				*mlx_window;
	char				player_char;
	double				player_angle_rad;
	t_coordinate		player_position;
	t_coordinate		player_dir;
	t_coordinate		plane;
	t_map				map;
	t_image 			image;
	t_image 			initial;
	t_image				gun[15];
	//t_image				door[5];
	t_text				textures;
	int 				rotation;
	int					minmap_square;
	int					reload;
	int					shot;
	bool				start_game;
	bool				has_bullet;
	
}						t_cub;

//init.c
t_cub		*init_cub_struct();
void		init_mlx(t_cub *cub);
void		define_initial_rotation(t_cub *cub);
void		define_player_vectors(t_cub *cub);
void		init_textures(t_cub *cub);

//raycasting.c
int		ray_casting(t_cub *cub);
t_ray	*calculate_ray(t_cub * cub, int ray_id);
void	calculate_deltas(t_ray *ray);
void	increment_to_next_intersection(t_ray *ray);
void	calculate_wall_distance(t_ray *ray);

//draw.c
void	draw_floor_ceiling(t_cub *cub, t_ray *ray);
int		define_texture_orientation(t_cub *cub, t_ray *ray);
void	draw_textures(t_cub *cub, t_ray *ray);

//move_player.c
void	move_player(int key, t_cub *cub);
void	move_player_up(t_cub *cub, int quadrant);
void	move_player_down(t_cub *cub, int quadrant);
void	move_player_left(t_cub *cub, int quadrant);
void	move_player_right(t_cub *cub, int quadrant);

//rotate.c
void	rotate_player(int key, t_cub *cub);
int 	check_quadrant(double player_angle);
void 	change_player_position(t_coordinate *new_pos, t_cub *cub);

//utils.c
int			handle_input(int key, t_cub *cub);
void 		my_mlx_pixel_put(t_image *img, int x, int y, int color);
unsigned int get_color_from_pixel(t_image *img, int x, int y);
char		*ft_strstr(char *str, char *to_find);
void		resize_image(t_image *src, t_image *dst, int new_width, int new_height);
void		draw_initial_image(t_cub *cub);
void		init_image_xpm(t_cub *cub, t_image *i, char *path);
void		init_new_image(t_cub *cub, t_image *image, int width, int height);


//parsing/parsing.c
int		find_extension(char *map, char *ext);
int		parsing(t_cub *cub, char *argv);
char	**get_matrix_from_file(t_cub *cub, char *file);
int		count_lines(char *file);
int		find_player_position(t_cub *cub);

//parsing/texture.c
int		init_texture_color_names(t_cub *cub);
char	*get_info(char *file, int flag);
int		is_valid_textures(t_cub *cub);
int		duplicate_texture_or_color(t_cub *cub);
int		is_valid_colors(t_cub *cub);

//parsing/color.c
int		has_three_numbers(char *str);
int		ft_isdigit_space_tab(int c);
void	save_rgb(t_cub *cub);
int		rgb_to_hex(int rgb[3]);

//parsing/map.c
char	**extract_map(t_cub *cub, char **file, int y);
char 	*get_map_line(char *file, int size);
int		find_biggest_line(char **map);
int		empty_line(char *line);
int		map_size_valid_char(char **file, int i);

//parsing/map_walls.c
int		closed_by_walls(t_cub *cub, char **map);
int		find_wall_horizontaly(char **map, int y, int x);
int		find_wall_up_down(t_cub *cub, char **map, int y, int x);

//frees.c
void	free_matrix(char **matrix);
void	free_map_struct(t_map *map);
void	free_gun(t_cub *cub);
void	panic(t_cub *cub);
void	free_textures(t_cub *cub);
void	error_message(char *str);

#endif