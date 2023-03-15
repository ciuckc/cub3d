/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:42:15 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/15 13:47:05 by mbatstra         ###   ########.fr       */
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

// parse() will validate that the map is playable, closed off and all the right
// texture info is present and then load everything in to the right structs
void		parse(int argc, char **argv, t_vars *vars);
// get tile value at given position
int8_t		mapindex(t_map *map, int x, int y);

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

// construct color from seperate channels
uint32_t	get_rgba(int r, int g, int b, int a);
// get pixel value at position in image
uint32_t	get_pixel(mlx_image_t *img, t_vect2 i);
// get specific channel from color
uint8_t		get_red(uint32_t clr);
uint8_t		get_grn(uint32_t clr);
uint8_t		get_blu(uint32_t clr);
uint8_t		get_alpha(uint32_t clr);
// darken color based on distance
uint32_t	apply_shade(uint32_t clr, double dist);
// invert color
uint32_t	inv_color(uint32_t clr);

// cast a single ray and return the first x and y intersections with a wall
t_fvect2	cast_ray(t_map *map, t_player *player, t_fvect2 raydir);
// floorcasting
void		draw_floor(t_vars *vars);
// draw a single vertical wall segment
void		draw_line(t_vars *v, uint32_t x, double ang, t_fvect2 *p);
// driver code for wall and floorcasting as well as sprites
void		render(void *param);

// all these functions do is init some mlx images that get pushed to the
// render queue so mlx handles everything afterwards
void		render2d_init(t_vars *vars);
// update the minimap image
void		render2d_minimap(void *param);

// init the interact action image
void		init_interact(t_vars *vars);
// checks if the game is won or lost
void		game_hook(void *param);
// capture all keyboard input and handle it
// some things that happen here are not really player related
// move them to a more appropriate function
void		player_hook(void *param);
// move enemies towards player
void		enemy_hook(void *param);

// draw a sprite using the distance for all vertical segments calculated
// during raycasting
void		sprite_display(t_vars *vars, double *z_arr);
// init sprite structs
void		sprites_init(t_vars *vars);
// init animated sprites
void		collec_init(t_vars *vars, t_sprite *collec, t_vect2 pos);
// check if animated sprite needs to display a new frame
void		collec_update_frame(t_sprite *collec, double t_delta);
// put_pixel wrapper that applies shading and inverts colors when necessary
void		sprite_put_pixel(t_vars *v, t_vect2 i, t_vect2 img_i, t_sprite *s);
// sort sprites based on distance from the player so they get draw in the 
// right order
void		sprites_sort(t_vars *vars);

#endif
