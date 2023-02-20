/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/10 23:09:42 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/17 16:13:20 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

// calculate new position based on pressed key
// movement vector can be set directly instead of returning the value
// because the collision algorithm only cares about
// the direction the player last *tried* to move in
static t_fvect2	st_get_pos(t_player *plyr, mlx_t *mlx)
{	
	t_fvect2	pos;

	pos = vec(-1.0, 0.0);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		pos = vec_add(vec_mul(plyr->dir, MOV_SPD), plyr->pos);
		plyr->mov = plyr->dir;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		pos = vec_add(vec_mul(vec_rot(plyr->dir, M_PI), MOV_SPD), plyr->pos);
		plyr->mov = vec_rot(plyr->dir, M_PI);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		pos = vec_add(vec_mul(vec_rot(plyr->dir, -M_PI_2), MOV_SPD), plyr->pos);
		plyr->mov = vec_rot(plyr->dir, -M_PI_2);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		pos = vec_add(vec_mul(vec_rot(plyr->dir, M_PI_2), MOV_SPD), plyr->pos);
		plyr->mov = vec_rot(plyr->dir, M_PI_2);
	}
	return (pos);
}

// fetch new position and perform collision checks
// if there is only one wall blocking movement
// move proportionally along the unblocked axis
static void	st_move_player(t_player *plyr, t_map *map, mlx_t *mlx)
{
	t_fvect2	pos;
	t_fvect2	dist;

	pos = st_get_pos(plyr, mlx);
	if (pos.x == -1.0)
		return ;
	dist = cast_ray(map, plyr, plyr->mov);
	if (dist.x > MOV_SPD && dist.y > MOV_SPD)
		plyr->pos = pos;
	else if (dist.x > dist.y)
	{
		pos = vec_add(plyr->pos, vec_mul(vec(plyr->mov.x, 0.0), MOV_SPD));
		if (mapindex(map, floor(pos.x), floor(pos.y)) != WALL)
			plyr->pos = pos;
	}
	else
	{
		pos = vec_add(plyr->pos, vec_mul(vec(plyr->mov.y, 0.0), MOV_SPD));
		if (mapindex(map, floor(pos.x), floor(pos.y)) != WALL)
			plyr->pos = pos;
	}
}

// capture all keyboard input
// check if mlx needs other cleanup!!!
void	player_hook(void *param)
{
	t_player	*player;
	t_map		*map;
	mlx_t		*mlx;

	player = &((t_vars *)param)->player;
	map = &((t_vars *)param)->map;
	mlx = ((t_vars *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		exit(EXIT_SUCCESS);
	}
	st_move_player(player, map, mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->dir = vec_rot(player->dir, -ROT_SPD);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->dir = vec_rot(player->dir, ROT_SPD);
}
