/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:42:15 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/14 15:57:14 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <assert.h>
# include "MLX42.h"
# include "settings.h"
# include "defs.h"
# include "structs.h"
# include "libft.h"
# include <stdio.h>

// capture keyboard input
void		player_hook(void *param);
void		enemy_hook(void *param);

/**
 * @brief Makes sure that the a map is provided, the map name provided is a 
 * valid .cub map, then it creates a full string out of the content. Then it
 * creates a matrix that simbolizes the map contents and another array which
 * stores of 
 * @param argc 
 * @param argv 
 * @param vars 
 */
void		parse(int argc, char **argv, t_vars *vars);
// render
int8_t		mapindex(t_map *map, int x, int y);
void		game_hook(void *param);

// round double vector to int vector
t_vect2		vec_round(t_fvect2 vec);
// returns the sum of two vectors
t_fvect2	vec_add(t_fvect2 v1, t_fvect2 v2);
// returns the difference of two vectors
t_fvect2	vec_sub(t_fvect2 v1, t_fvect2 v2);
// rotates vec by angle radians
t_fvect2	vec_rot(t_fvect2 vec, double angle);
// multiply a vector by a scalar
t_fvect2	vec_mul(t_fvect2 vec, double factor);
// get length of vector
double		vec_len(t_fvect2 vec);
// dot product of two vectors
double		vec_dot(t_fvect2 v1, t_fvect2 v2);
// get angle between two vectors
double		vec_angle(t_fvect2 v1, t_fvect2 v2);
// construct vector
t_fvect2	vec(double x, double y);

// functions to extract components or construct a color
uint32_t	get_rgba(int r, int g, int b, int a);
uint32_t	get_pixel(mlx_image_t *img, t_vect2 i);
uint8_t		get_red(uint32_t clr);
uint8_t		get_grn(uint32_t clr);
uint8_t		get_blu(uint32_t clr);
uint8_t		get_alpha(uint32_t clr);
uint32_t	apply_shade(uint32_t clr, double dist);
uint32_t	inv_color(uint32_t clr);

// cast a single ray
t_fvect2	cast_ray(t_map *map, t_player *player, t_fvect2 raydir);
uint32_t	set_pixel_color(t_vars *vars, mlx_image_t *img, t_fvect2 *coords);
void		draw_floor(t_vars *vars);
void		draw_line(t_vars *v, uint32_t x, double ang, t_fvect2 *p);
void		render(void *param);

// render2d
void		render2d_init(t_vars *vars);
void		render2d_minimap(void *param);
void		sprite_display(t_vars *vars, double *z_arr);
void		sprites_init(t_vars *vars);
void		collec_init(t_vars *vars, t_sprite *collec, t_vect2 pos);
void		init_interact(t_vars *vars);
void		collec_update_frame(t_sprite *collec, double t_delta);
void		sprite_put_pixel(t_vars *vars, t_vect2 i, t_vect2 img_i, \
	t_sprite *spr);
void		sprites_sort(t_vars *vars);

#endif
