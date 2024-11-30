/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:40:06 by ismirand          #+#    #+#             */
/*   Updated: 2024/11/30 16:34:25 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "cub.h"

//bonus/minimap.c
int				minimap(t_cub *cub);
void			draw_element_minimap(t_cub *cub, int x, int y, int color);
void			draw_player_minimap(t_cub *cub);
void			draw_rays_minimap(t_cub *cub);
void			draw_one_ray_minimap(t_cub *cub, t_coordinate *ray_vector);

//bonus/gun.c
void			init_gun(t_cub *cub);
t_image			*define_gun_sprite(t_cub *cub);
void			draw_gun(t_cub *cub);

//bonus/raycasting.c
int				ray_casting_bonus(t_cub *cub);
void			ray_casting_loop(t_cub *cub);

//bonus/door.c
bool			is_door(int y, int x, t_cub *cub);
t_coordinate	is_close_to_door(t_cub *cub);
int				handle_input_bonus(int key, t_cub *cub);

//bonus/mouse.c
int				handle_mouse_move(int x, int y, t_cub *cub);
int				handle_mouse(int key, int x, int y, t_cub *cub);

#endif