/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 23:09:42 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/15 20:02:43 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

void	player_hook(void *param)
{
	t_player	*player;
	mlx_t		*mlx;

	player = &((t_vars *)param)->player;
	mlx = ((t_vars *)param)->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx); //run other cleanup as well
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player->pos = vec_add(vec_mul(player->dir, 0.025), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player->pos = vec_add(vec_mul(vec_rot(player->dir, M_PI), 0.025), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player->pos = vec_add(vec_mul(vec_rot(player->dir, -M_PI_2), 0.025), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player->pos = vec_add(vec_mul(vec_rot(player->dir, M_PI_2), 0.025), player->pos);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->dir = vec_rot(player->dir, -0.050);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->dir = vec_rot(player->dir, 0.050);
}

void	player_init(t_vars *vars)
{
	t_player	*player;

	player = &((t_vars *)vars)->player;
	player->pos = vec(2.5, 2.5);
	player->dir = vec(1.0, 0.0);
	player->player_img = mlx_new_image(vars->mlx, 8, 8);
	fill_img(player->player_img, 0xffffffff);
	mlx_image_to_window(vars->mlx, player->player_img, WIDTH / 2, HEIGHT / 2);
}

void	player_routine(void *vars)
{
	mlx_image_t	*player_img;
	t_fvect2	pos;

	vars = (t_vars *)vars;
	player_img = ((t_vars *)vars)->player.player_img;
	pos = ((t_vars *)vars)->player.pos;
	player_img->instances[0].x = pos.x * TILESIZE;
	player_img->instances[0].y = pos.y * TILESIZE;
}

void	db_linetest(void *param)
{
	t_vect2		orgn;
	t_vect2		end;
	t_vars		*vars;

	vars = (t_vars *)param;
	orgn = vec_round(vec_mul(vars->player.pos, TILESIZE));
	end = vec_round(vec_add(vec_mul(vars->player.dir, 25), vec_mul(vars->player.pos, TILESIZE)));
	ft_memset(vars->canvas->pixels, 0, WIDTH * HEIGHT * sizeof(int));
	line(orgn, end, 0xffffffff, vars);
	end = vec_round(vec_add(vec_mul(vars->player.dir, TILESIZE * cast_ray(&vars->map, &vars->player, vars->player.dir)), vec_mul(vars->player.pos, TILESIZE)));
	line(orgn, end, 0xff0000ff, vars);
}
