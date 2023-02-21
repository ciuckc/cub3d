/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:42:15 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/21 19:24:35 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <assert.h>
# include "MLX42.h"
# include <stdio.h>

# define WIDTH 1024
# define HEIGHT 1024

# define MAPSCALE 0.275
# define TPM 8
# define PLAYER2D_CLR 0xffffffff

# define ANIM_FR 0.15

# define MOV_SPD 0.05
# define ROT_SPD 0.05
# define ENEMY_SPD 0.005
# define FOV 1.0471976 // pi / 3

# define FLOOR 0
# define WALL 1
# define START_POS 2
# define UNREACH 3
# define COLLEC 4
# define EXIT 5
# define ENEMY 6

# define Z_LVL_BACKGRND -1
# define Z_LVL_CANVAS 0
# define Z_LVL_MINIMAP 1
# define Z_LVL_HUD 2

/*
Chars which are valid map content -> SUPER IMPORTANT FOR LATER IF WE ADD
MORE SPRITES OR OTHER STUFF.
*/
# define MAP_CONTENT " 01NSWEHC"
# define TEXTURES "NSWEFC"

# define HUD_PATH "assets/hud3.png"
# define SKY_PATH "assets/sky3.xpm42"
# define ENEMY1_PATH "assets/ghoulie.xpm42"
# define ENEMY2_PATH "assets/ghoulie2.xpm42"
# define COLLEC_PATH "assets/crystal.xpm42"
# define EXIT_PATH "assets/portal.xpm42"

// File extension

# define FILE_EXT ".xpm42"

/*
	vector defines for drawing to screen
*/
# define IMG_POS 0
# define LN_START 1
# define LN_END 2

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
	t_fvect2	pos;	// player position on map, 1 tile == 1 unit
	t_fvect2	dir;	// unit vector player direction
	t_fvect2	mov;	// unit vector last player movement
}			t_player;

typedef struct s_sprite {
	mlx_image_t	*tex;
	t_fvect2	pos;
	uint8_t		frame;
	xpm_t		*pix_arr[7];
	bool		is_animated;
	bool		is_movable;
}			t_sprite;

/**
 * @brief Map struct with size and pointer to the map contents.
 * 
 */
typedef struct s_map {
	t_vect2		size;
	uint8_t		*grid;
}			t_map;

/**
 *@brief Used for indexing paths to images in the array of textures.
 * 
 */
enum e_content {
	N,
	S,
	W,
	E,
	F,
	C,
	X
};

/**
 * @brief Program struct.
 * 
 */
typedef struct s_vars {
	mlx_image_t	*canvas;
	mlx_image_t	*texture[sizeof(TEXTURES) - 1];
	mlx_image_t	*texture2d[5];
	uint32_t	floor_clr;
	uint32_t	ceil_clr;
	t_player	player;
	t_sprite	*sprite;
	uint32_t	num_sprites;
	t_fvect2	dst;
	t_map		map;
	mlx_t		*mlx;
}			t_vars;

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
uint32_t	get_pixel(mlx_image_t *img, t_vect2 i);
uint8_t		get_red(uint32_t clr);
uint8_t		get_grn(uint32_t clr);
uint8_t		get_blu(uint32_t clr);
uint8_t		get_alpha(uint32_t clr);

// cast a single ray
uint32_t	set_pixel_color(t_vars *vars, mlx_image_t *img, t_fvect2 *coords);
void		draw_line(t_vars *vars, uint32_t x, double angle, t_fvect2 \
	*pos);
t_fvect2	cast_ray(t_map *map, t_player *player, t_fvect2 raydir);
void		render(void *param);

// render2d
void		render2d_init(t_vars *vars);
void		render2d_minimap(void *param);
void		sprite_display(t_vars *vars, double *z_arr);
void		sprites_init(t_vars *vars);
void		collec_init(t_vars *vars, t_sprite *collec, t_vect2 pos);
void		collec_update_frame(t_sprite *collec, double delta);
void		sprite_put_pixel(t_vars *vars, t_vect2 i, t_vect2 img_i, t_sprite *spr);
void		sprites_sort(void *param);

#endif
