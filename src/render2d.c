/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:21:43 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/17 16:05:38 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

int	mapindex(t_map *map, int x, int y)
{
	return (map->grid[x + y * map->size.x]);
}

static void	st_fill_sqr(t_map *map, uint32_t x, uint32_t y, uint32_t clr)
{
	t_vect2	i;

	i.y = 0;
	while (i.y < MAPSIZE / map->size.y)
	{
		i.x = 0;
		while (i.x < MAPSIZE / map->size.x)
		{
			mlx_put_pixel(map->minimap, x + i.x, y + i.y, clr);
			i.x++;
		}
		i.y++;
	}
}

void	init_minimap(mlx_t *mlx, t_map *map)
{
	uint32_t	clr;
	uint32_t	tilesize;
	t_vect2		pos;

	if (map->size.x > map->size.y)
		tilesize = MAPSIZE / map->size.x;
	else
		tilesize = MAPSIZE / map->size.y;
	map->minimap = mlx_new_image(mlx, MAPSIZE, MAPSIZE);
	pos.y = 0;
	printf("%d, %d\n---\n", map->size.x, map->size.y);
	while (pos.y < map->size.y)
	{
		pos.x = 0;
		while (pos.x < map->size.x)
		{
			clr = 0x99999999;
			if (mapindex(map, pos.x, pos.y) != WALL)
				clr = 0x55555599;
			st_fill_sqr(map, pos.x * tilesize, pos.y * tilesize, clr);
			pos.x++;
		}
		pos.y++;
	}
}
