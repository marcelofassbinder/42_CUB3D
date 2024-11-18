#ifndef CUB_BONUS_H
#define CUB_BONUS_H

#include "cub.h"

#define MINMAP_SQUARE 15

int		minimap(t_cub *cub);
int		ray_casting_bonus(t_cub *cub);
void	draw_element_minimap(t_cub *cub, int x, int y, int color);
void	draw_player_minimap(t_cub *cub);
void	draw_rays_minimap(t_cub *cub);
void	draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector);



#endif