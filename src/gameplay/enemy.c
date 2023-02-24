/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:29:23 by mbatstra          #+#    #+#             */
/*   Updated: 2023/02/23 19:32:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include <stdio.h>

void	enemy_hook(void *param)
{
	uint32_t	i;
	t_fvect2	pos;
	t_vars		*vars;
	double		inv_len;

	vars = (t_vars *)param;
	i = 0;
	while (i < vars->num_sprites)
	{
		if (vars->sprite[i].is_movable)
		{
			pos.x = vars->player.pos.x - vars->sprite[i].pos.x;
			pos.y = vars->player.pos.y - vars->sprite[i].pos.y;
			inv_len = 1 / vec_len(pos);
			pos = vec_mul(pos, inv_len * ENEMY_SPD);
			vars->sprite[i].pos = vec_add(vars->sprite[i].pos, pos);
		}
		i++;
	}
}
