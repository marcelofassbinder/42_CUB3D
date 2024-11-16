#ifndef CUB_BONUS_H
#define CUB_BONUS_H

#include "cub.h"

#define MINMAP_SQUARE 15

int		minimap(t_cub *cub);
int		ray_casting_bonus(t_cub *cub);
void	render_element_minimap(t_cub *cub, int x, int y, int color);
void	render_player_minimap(t_cub *cub);


#endif