/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 17:21:43 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/25 19:40:25 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

static void	st_fill_sqr(t_vars *vars, uint32_t x, uint32_t y, uint32_t clr)
{
	int32_t	tilesize;
	int32_t	mapsize;
	t_vect2	i;

	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	tilesize = mapsize / TPM;
	i.y = 0;
	while (i.y < tilesize)
	{
		i.x = 0;
		while (i.x < tilesize)
		{
			mlx_put_pixel(vars->texture2d[1], x + i.x, y + i.y, clr);
			i.x++;
		}
		i.y++;
	}
}

bool	st_inbounds(t_map *map, t_vect2 pos, t_vect2 i)
{
	return (pos.x + i.x >= 0 && pos.y + i.y >= 0 && \
			pos.x + i.x < map->size.x && pos.y + i.y < map->size.y);
}

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

void	render2d_minimap(void *param)
{
	uint32_t	tilesize;
	uint32_t	mapsize;
	t_vars		*vars;

	vars = (t_vars *)param;
	if (WIDTH >= HEIGHT)
		mapsize = WIDTH * MAPSCALE;
	else
		mapsize = HEIGHT * MAPSCALE;
	tilesize = mapsize / TPM;
	st_drawmap(vars, tilesize);
	st_mapoffset(vars, tilesize, mapsize);
}
