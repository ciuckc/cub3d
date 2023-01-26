/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:49:42 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/26 19:44:12 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

// calculate the total distance a ray needs to go from one 
// horizontal/vertical gridline to the next
// the actual formula is abs(|raydir| / raydir.x) but since we use
// a unit vector we can substitute 1.0 and scale it later
static t_fvect2	st_delta_dist(t_fvect2 raydir)
{
	t_fvect2	dist;

	dist.x = fabs(1.0 / raydir.x);
	dist.y = fabs(1.0 / raydir.y);
	return (dist);
}

// same approach as st_delta_dist() but with compensation for the 
// player distance from the first edge
static t_fvect2	st_side_dist(t_player *player, t_vect2 step, t_fvect2 raydir)
{
	t_fvect2	dist;
	t_fvect2	side;
	t_vect2		player_tile;

	player_tile.x = floor(player->pos.x);
	player_tile.y = floor(player->pos.y);
	if (step.x < 0)
		side.x = player->pos.x - player_tile.x;
	else
		side.x = player_tile.x + 1 - player->pos.x;
	if (step.y < 0)
		side.y = player->pos.y - player_tile.y;
	else
		side.y = player_tile.y + 1 - player->pos.y;
	dist = st_delta_dist(raydir);
	dist.x *= side.x;
	dist.y *= side.y;
	return (dist);
}

// determine in which quadrant ray is heading
static t_vect2	st_get_step(t_fvect2 raydir)
{
	t_vect2	step;

	if (raydir.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (raydir.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);
}

// this could be one function but norminette playin
// still room for some optimization here because step is computed twice
// and delta only needs to be done once per ray instead of once per iteration
static void	st_iter_ray(t_fvect2 *dst, t_fvect2 dir, t_vect2 *pos, t_map *map)
{
	t_fvect2	delta;
	t_vect2		step;

	delta = st_delta_dist(dir);
	step = st_get_step(dir);
	if (dst->x < dst->y)
	{
		pos->x += step.x;
		if (mapindex(map, pos->x, pos->y) == WALL)
			return ;
		dst->x += delta.x;
	}
	else
	{
		pos->y += step.y;
		if (mapindex(map, pos->x, pos->y) == WALL)
			return ;
		dst->y += delta.y;
	}
}

// keep checking intersections of ray and gridlines until a wall is hit
// dist: the distance to the nearest x and y instersect with a wall
// delta: distance to next gridline to be added each iteration
// ray_pos: current tile the tip of the ray is in
// step: ray heading
t_fvect2	cast_ray(t_map *map, t_player *player, t_fvect2 raydir)
{
	t_fvect2	dist;
	t_vect2		step;
	t_vect2		ray_pos;

	step = st_get_step(raydir);
	ray_pos.x = floor(player->pos.x);
	ray_pos.y = floor(player->pos.y);
	dist = st_side_dist(player, step, raydir);
	while (mapindex(map, ray_pos.x, ray_pos.y) != WALL)
		st_iter_ray(&dist, raydir, &ray_pos, map);
	return (dist);
}
