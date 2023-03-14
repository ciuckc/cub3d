/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:44:17 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/14 15:18:20 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"
# include "defs.h"

// 2d integer vector
typedef struct s_vect2 {
	int32_t	x;
	int32_t	y;
}			t_vect2;

// 2d double vector
typedef struct s_fvect2 {
	double	x;
	double	y;
}			t_fvect2;

// all player info
// pos is the map position of the player
// dir is a unit vector holding the direction player is facing
// mov is a unit vector holding the direction the player last tried to move
typedef struct s_player {
	t_fvect2	pos;
	t_fvect2	dir;
	t_fvect2	mov;
}			t_player;

// a bit hacky but the sprite struct can be used to represent one of three
// types of entities: enemies, collectibles, and exit
// the flags are used to indicate what behaviour the sprite has
// every sprite has at least tex and pos
// frame, t_delta, and pix_arr are for sprites with animation
typedef struct s_sprite {
	mlx_image_t	*tex;
	t_fvect2	pos;
	uint8_t		frame;
	double		t_delta;
	xpm_t		*pix_arr[7];
	bool		is_animated;
	bool		is_movable;
	bool		is_toggled;
}			t_sprite;

// map stored as a 1d row by row array with vector containing map dimensions
typedef struct s_map {
	t_vect2		size;
	uint8_t		*grid;
}			t_map;

// program struct containing all info necessary for rendering
// and handling events
typedef struct s_vars {
	mlx_image_t	*canvas;
	mlx_image_t	*texture[sizeof(TEXTURES) - 1];
	mlx_image_t	*texture2d[6];
	uint32_t	floor_clr;
	uint32_t	ceil_clr;
	t_player	player;
	t_sprite	*sprite;
	uint32_t	num_sprites;
	t_fvect2	dst;
	t_map		map;
	mlx_t		*mlx;
}			t_vars;

#endif
