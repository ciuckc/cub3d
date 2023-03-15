/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:14:16 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/14 15:29:45 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// allowed chars in map file
// texture and color declarations not included
# define MAP_CONTENT " 01NSWEHC"
// different allowed textures
# define TEXTURES "NSWEFC"
// map file extension
# define FILE_EXT ".xpm42"

// textures for all 2d elements and sprites
# define HUD_PATH "assets/hud3.png"
# define SKY_PATH "assets/sky3.xpm42"
# define ENEMY1_PATH "assets/ghoulie.xpm42"
# define ENEMY2_PATH "assets/ghoulie2.xpm42"
# define COLLEC_PATH "assets/crystal.xpm42"
# define EXIT_PATH "assets/portal.xpm42"
# define INTERACT_PATH "assets/interact.png"

// macro identifiers for map values
enum e_mapvals	{
	FLOOR,
	WALL,
	START_POS,
	UNREACH,
	COLLEC,
	EXIT,
	ENEMY
};

// z levels for all graphical components
enum e_zlevels	{
	Z_LVL_BACKGRND,
	Z_LVL_CANVAS,
	Z_LVL_MINIMAP,
	Z_LVL_MAPDOT,
	Z_LVL_HUD
};

// vector indices for renderer
enum e_vec_indices	{
	IMG_POS,
	LN_START,
	LN_END
};

// allowed map contents
enum e_content {
	N,
	S,
	W,
	E,
	F,
	C,
	X
};

#endif
