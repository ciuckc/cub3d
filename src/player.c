/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:09:42 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/11 17:54:05 by mbatstra         ###   ########.fr       */
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
// because theoretically, the collision algorithm only cares about
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

// use movement vector to project a point and see if it's inside a wall
// right now a magic number defines de player boundary
// if you cut a corner tight enough you can clip through
// maybe use a raycast and check if dist is below buondary thershold instead
static bool	st_is_collision(t_player *plyr, t_map *map)
{
	t_fvect2	project_pos;

	project_pos = vec_add(plyr->pos, vec_mul(plyr->mov, 0.1));
	project_pos.x = floor(project_pos.x);
	project_pos.y = floor(project_pos.y);
	return (mapindex(map, (int)project_pos.x, (int)project_pos.y) == WALL);
}

// driver code for above two functions
static void	st_move_player(t_player *plyr, t_map *map, mlx_t *mlx)
{
	t_fvect2	pos;

	pos = st_get_pos(plyr, mlx);
	if (pos.x == -1.0)
		return ;
	if (!st_is_collision(plyr, map))
		plyr->pos = pos;
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

void	player_init(t_vars *vars)
{
	t_player	*player;

	player = &((t_vars *)vars)->player;
	player->pos = vec(2.5, 2.5);
	player->dir = vec(1.0, 0.0);
	player->mov = vec(1.0, 0.0);
}
