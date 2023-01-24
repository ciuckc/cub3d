/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map_range.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 20:02:32 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/24 15:09:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int32_t	st_get_first_reached_y(t_map unsan_map, t_tile **tiles)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	while (y < unsan_map.size.y)
	{
		while (x < unsan_map.size.x)
		{
			if (tiles[y][x].type == FLOOR && tiles[y][x].reached)
				return (y);
			x++;
		}
		x = 0;
		y++;
	}
	return (y);
}

static int32_t	st_get_last_reached_y(t_map unsan_map, t_tile **tiles)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = unsan_map.size.y - 1;
	while (y > 0)
	{
		while (x < unsan_map.size.x)
		{
			if (tiles[y][x].type == FLOOR && tiles[y][x].reached)
				return (y);
			x++;
		}
		x = 0;
		y--;
	}
	return (y);
}

static int32_t	st_get_min_x_pos(t_map unsan_map, t_tile **tile_map)
{
	int32_t	x;
	int32_t	y;
	int32_t	min_x;

	x = 0;
	min_x = INT32_MAX;
	y = 0;
	while (y < unsan_map.size.y)
	{
		x = 0;
		while (x < unsan_map.size.x)
		{
			if (tile_map[y][x].type == FLOOR && tile_map[y][x].reached)
				break ;
			x++;
		}
		if (x < min_x)
			min_x = x;
		y++;
	}
	return (min_x);
}

static int32_t	st_get_max_x_pos(t_map unsan_map, t_tile **tile_map)
{
	int32_t	x;
	int32_t	y;
	int32_t	max_x;

	y = unsan_map.size.y - 1;
	x = unsan_map.size.x - 1;
	max_x = INT32_MIN;
	while (y > 0)
	{
		x = unsan_map.size.x - 1;
		while (x > 0)
		{
			if (tile_map[y][x].type == FLOOR && tile_map[y][x].reached)
				break ;
			x--;
		}
		if (x > max_x)
			max_x = x;
		y--;
	}
	return (max_x);
}

void	get_map_range(t_map *unsan_map, t_tile **tiles, t_vect2 *ranges)
{
	ranges[FIRST].y = st_get_first_reached_y(*unsan_map, tiles);
	ranges[LAST].y = st_get_last_reached_y(*unsan_map, tiles);
	ranges[FIRST].x = st_get_min_x_pos(*unsan_map, tiles);
	ranges[LAST].x = st_get_max_x_pos(*unsan_map, tiles);
}
