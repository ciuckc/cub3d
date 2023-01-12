/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:42:15 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/12 20:08:33 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "MLX42.h"

# define WIDTH 1024
# define HEIGHT 1024
# define MOV_SPEED 0.025
# define ROT_SPEED 0.05
// later tilesize should become a scaling factor for the minimap
# define TILESIZE 85
# define FOV M_PI / 3.0
# define FLOOR 0
# define WALL 1
# define START_POS 2

/*
Chars which are valid map content -> SUPER IMPORTANT FOR LATER IF WE ADD
MORE SPRITES OR OTHER STUFF.
*/
# define MAP_CONTENT " 01X"
# define TEXTURES "NSWEFC"

// File extension

# define FILE_EXT ".xpm42"

typedef struct s_vect2 {
	int32_t	x;
	int32_t	y;
}			t_vect2;

typedef struct s_fvect2 {
	double	x;
	double	y;
}			t_fvect2;

/**
 * @brief Stores current position of the player and the direction
 * the player is facing.
 * 
 * @param pos Position on map. 1 tile == 1 unit.
 * @param dir Direction vector which holds the current direction
 * the player is facing
 */
typedef struct s_player {
	t_fvect2	pos;
	t_fvect2	dir;
}			t_player;

/**
 * @brief Map struct with size and pointer to the map contents.
 * 
 */
typedef struct s_map {
	t_vect2	size;
	int32_t	*grid;
}			t_map;

/**
 *@brief Used for indexing paths to images in the array of textures.
 * 
 */
typedef enum e_content {
	N,
	S,
	W,
	E,
	F,
	C,
	X
}			t_cont;

union u_tex {
	mlx_image_t	*tex;
	uint32_t	clr;
};

/**
 * @brief Texture data.
 * 
 */
typedef struct s_tex {
	union u_tex	elem;
	bool		is_clr;
}			t_tex;

/**
 * @brief Program struct.
 * 
 */
typedef struct s_vars {
	mlx_image_t	*canvas;
	t_player	player;
	t_tex		texture[sizeof(TEXTURES) - 1];
	t_map		map;
	mlx_t		*mlx;
}			t_vars;

// capture keyboard input
void		player_hook(void *param);
// initialize pos, dir and player image
void		player_init(t_vars *vars);

// atm parser only supports rectangular maps!!!
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
void		render(void *param);

#endif
