/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/10 23:09:42 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/16 20:36:01 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

// capture all keyboard input
// check if mlx needs other cleanup!!!
void	player_hook(void *param)
{
	t_player	*player;
	mlx_t		*mlx;

	player = &((t_vars *)param)->player;
	mlx = ((t_vars *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player->pos = vec_add(vec_mul(player->dir, MOV_SPEED), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->pos = \
		vec_add(vec_mul(vec_rot(player->dir, M_PI), MOV_SPEED), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->pos = \
		vec_add(vec_mul(vec_rot(player->dir, -M_PI_2), MOV_SPEED), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->pos = \
		vec_add(vec_mul(vec_rot(player->dir, M_PI_2), MOV_SPEED), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->dir = vec_rot(player->dir, -ROT_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->dir = vec_rot(player->dir, ROT_SPEED);
}
