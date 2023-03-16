/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 14:58:19 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/16 18:47:35 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42.h"
#include "cub3d.h"

bool	st_won(t_player *plyr, t_sprite *sprt, uint32_t num_sprt, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < num_sprt && mapindex(map, sprt[i].pos.x, sprt[i].pos.y) != EXIT)
		i++;
	if (i == num_sprt || hypot(sprt[i].pos.x - plyr->pos.x, \
							sprt[i].pos.y - plyr->pos.y) > 0.1)
		return (false);
	i = 0;
	while (i < num_sprt)
	{
		if (sprt[i].is_animated && !sprt[i].is_toggled)
			return (false);
		i++;
	}
	return (true);
}

bool	st_lost(t_player *plyr, t_sprite *sprt, uint32_t num_sprt)
{
	size_t	i;

	i = 0;
	while (i < num_sprt)
	{
		if (sprt[i].is_movable && hypot(sprt[i].pos.x - plyr->pos.x, \
										sprt[i].pos.y - plyr->pos.y) < 0.05)
			return (true);
		i++;
	}
	return (false);
}

void	game_hook(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (st_won(&vars->player, vars->sprite, vars->num_sprites, &vars->map))
	{
		printf("You won!\n");
		mlx_close_window(vars->mlx);
		mlx_terminate(vars->mlx);
		exit(EXIT_SUCCESS);
	}
	if (st_lost(&vars->player, vars->sprite, vars->num_sprites))
	{
		printf("You lost!\n");
		mlx_close_window(vars->mlx);
		mlx_terminate(vars->mlx);
		exit(EXIT_SUCCESS);
	}
}
