#ifndef CUB_BONUS_H
#define CUB_BONUS_H

#include "cub.h"


int		minimap(t_cub *cub);
int		ray_casting_bonus(t_cub *cub);
void	draw_element_minimap(t_cub *cub, int x, int y, int color);
void	draw_player_minimap(t_cub *cub);
void	draw_rays_minimap(t_cub *cub);
void	draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector);
void	draw_gun(t_cub *cub, t_image *gun);
void	shot(t_cub *cub);

//int		handle_input_bonus(int key, t_cub *cub);





#endif