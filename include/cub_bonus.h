#ifndef CUB_BONUS_H
#define CUB_BONUS_H

#include "cub.h"

//bonus/main_bonus.c
int		handle_mouse_move(int x, int y, t_cub *cub);
int		handle_mouse(int key, int x, int y, t_cub *cub);

//bonus/minimap.c
int		minimap(t_cub *cub);
void	draw_element_minimap(t_cub *cub, int x, int y, int color);
void	draw_player_minimap(t_cub *cub);
void	draw_rays_minimap(t_cub *cub);
void	draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector);

//bonus/gun.c
int		ray_casting_bonus(t_cub *cub);
void	init_gun(t_cub *cub);
t_image *define_gun_sprite(t_cub *cub);
void	draw_gun(t_cub *cub);

//int		handle_input_bonus(int key, t_cub *cub);

#endif