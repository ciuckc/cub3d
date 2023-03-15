/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/10 23:09:42 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/13 17:34:04 by scristia      ########   odam.nl         */
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
		pos = vec_add(plyr->pos, vec_mul(vec(0.0, plyr->mov.y), MOV_SPD));
		if (mapindex(map, floor(pos.x), floor(pos.y)) != WALL)
			plyr->pos = pos;
	}
}

void	st_move_sky(t_vars *vars, int32_t offset)
{
	mlx_image_t	*img1;
	mlx_image_t	*img2;

	img1 = vars->texture2d[3];
	img2 = vars->texture2d[4];
	img1->instances[0].x += offset;
	img1->instances[0].x %= WIDTH;
	if (img1->instances[0].x > 0)
		img2->instances[0].x = (img1->instances[0].x - WIDTH) % WIDTH;
	else
		img2->instances[0].x = (img1->instances[0].x + WIDTH) % WIDTH;
}

void	st_interact(t_vars *vars)
{
	t_fvect2	dist;
	uint8_t		i;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_SPACE))
	{
		vars->texture2d[5]->enabled = true;
		i = 0;
		while (!vars->sprite[i].is_animated && i < vars->num_sprites)
			i++;
		if (i == vars->num_sprites)
			return ;
		dist = vec_sub(vars->player.pos, vars->sprite[i].pos);
		if (dist.x < 0.1 && dist.y < 0.1)
			vars->sprite[i].is_toggled = true;
	}
	else
		vars->texture2d[5]->enabled = false;
}

// capture all keyboard input
// check if mlx needs other cleanup!!!
void	player_hook(void *param)
{
	t_player	*player;
	t_vars		*vars;
	t_map		*map;
	mlx_t		*mlx;

	vars = (t_vars *)param;
	player = &vars->player;
	map = &vars->map;
	mlx = vars->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
	st_move_player(player, map, mlx);
	st_interact(vars);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		player->dir = vec_rot(player->dir, -ROT_SPD);
		st_move_sky(vars, 8);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		player->dir = vec_rot(player->dir, ROT_SPD);
		st_move_sky(vars, -8);
	}
}
