/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:25:16 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/16 13:25:19 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42.h"
#include "parse.h"
#include "cub3d.h"

// fills a square inside minimap image with a given color
// parameters x and y are upper-left corner of square to fill
// x_off and y_off are coords inside square
static void	st_fill_sqr(t_vars *vars, uint32_t x, uint32_t y, uint32_t clr)
{
	uint32_t	tilesize;
	uint32_t	mapsize;
	uint32_t	x_off;
	uint32_t	y_off;

	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	tilesize = mapsize / TPM;
	y_off = 0;
	while (y_off < tilesize)
	{
		x_off = 0;
		while (x_off < tilesize)
		{
			mlx_put_pixel(vars->texture2d[1], x + x_off, y + y_off, clr);
			x_off++;
		}
		y_off++;
	}
}

// check if a position plus offset is a valid point on the map
bool	st_inbounds(t_map *map, t_vect2 pos, t_vect2 i)
{
	return (pos.x + i.x >= 0 && pos.y + i.y >= 0 && \
			pos.x + i.x < map->size.x && pos.y + i.y < map->size.y);
}

// draw entire minimap plus an extra row and column so the image can be
// moved without the image tearing
// pos is expressed in map coordinates and iterates over mapsize
// in tiles such that the player is always in the center
void	st_drawmap(t_vars *vars, uint32_t tilesize)
{
	uint32_t	clr;
	t_vect2		pos;
	t_vect2		i;

	pos.x = floor(vars->player.pos.x) - TPM / 2;
	pos.y = floor(vars->player.pos.y) - TPM / 2;
	i.y = 0;
	while (i.y <= TPM)
	{
		i.x = 0;
		while (i.x <= TPM)
		{
			clr = 0x99999999;
			if (st_inbounds(&vars->map, pos, i) && \
				mapindex(&vars->map, pos.x + i.x, pos.y + i.y) != WALL)
				clr = 0x55555599;
			st_fill_sqr(vars, i.x * tilesize, i.y * tilesize, clr);
			i.x++;
		}
		i.y++;
	}
}

// offset the minimap image so that the player is in the center
// any pixels beyond the minimap's borders get their aplha set to 0
void	st_mapoffset(t_vars *vars, uint32_t tilesize, uint32_t mapsize)
{
	mlx_image_t	*img;
	uint32_t	x;
	uint32_t	y;
	t_vect2		offset;

	offset.x = (vars->player.pos.x - floor(vars->player.pos.x)) * tilesize;
	offset.y = (vars->player.pos.y - floor(vars->player.pos.y)) * tilesize;
	img = vars->texture2d[1];
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (x - offset.x > mapsize || y - offset.y > mapsize)
				img->pixels[(x + y * img->width) * sizeof(uint32_t) + 3] = 0;
			x++;
		}
		y++;
	}
	img->instances[0].x = -offset.x;
	img->instances[0].y = -offset.y;
}

// driver function
// redraws the minimap every time the player moves to a new tile
// because the room to translate the image is exactly one tile
// on each frame, regardless of redrawing, translate and set alpha of image
void	render2d_minimap(void *param)
{
	static t_fvect2	last_pos;
	uint32_t		tilesize;
	uint32_t		mapsize;
	t_vars			*vars;

	vars = (t_vars *)param;
	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	tilesize = mapsize / TPM;
	if (vars->player.pos.x != last_pos.x || vars->player.pos.y != last_pos.y)
		st_drawmap(vars, tilesize);
	st_mapoffset(vars, tilesize, mapsize);
	last_pos = vars->player.pos;
}
