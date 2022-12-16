/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:42:15 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/16 16:05:46 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "MLX42.h"

# define WIDTH 512
# define HEIGHT 512
// later tilesize should become a scaling factor for the minimap
# define TILESIZE 85
# define FLOOR 0
# define WALL 1
# define START_POS 2

typedef struct s_vect2 {
	int32_t	x;
	int32_t	y;
}			t_vect2;

typedef struct s_fvect2 {
	double	x;
	double	y;
}			t_fvect2;

typedef struct s_player {
	mlx_image_t	*player_img; // this should later be moved to minimap renderer
	t_fvect2	pos;	// player position on map, 1 tile == 1 unit
	t_fvect2	dir;	// unit vector player direction
	t_fvect2	cam;	// camera "plane", perpendicular to direction
}			t_player;

typedef struct s_map {
	t_vect2	size;
	int32_t	*grid;
}			t_map;

typedef struct s_vars {
	mlx_image_t	*canvas;
	t_player	player;
	t_map		map;
	mlx_t		*mlx;
}			t_vars;

// capture keyboard input
void		player_hook(void *param);
// initialize pos, dir and player image
void		player_init(t_vars *vars);
// update player position
void		player_routine(void *vars);

// atm parser only supports rectangular maps!!!
void		parse(char **argv, t_map *map);
void		render2d(mlx_t *mlx, t_map *map);
void		fill_img(mlx_image_t *img, uint32_t clr);
void		line(t_vect2 start, t_vect2 end, int clr, t_vars *vars);
void		db_linetest(void *vars);
int			mapindex(t_map *map, int x, int y);

// round double vector to int vector
t_vect2		vec_round(t_fvect2 vec);
// returns the sum of two vectors
t_fvect2	vec_add(t_fvect2 v1, t_fvect2 v2);
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
uint8_t		get_red(uint32_t clr);
uint8_t		get_grn(uint32_t clr);
uint8_t		get_blu(uint32_t clr);
uint8_t		get_alpha(uint32_t clr);

// cast a single ray
t_fvect2	cast_ray(t_map *map, t_player *player, t_fvect2 raydir);

#endif
