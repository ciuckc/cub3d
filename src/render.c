/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:18:54 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/16 19:15:05 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

void	render(void *param)
{
	t_fvect2	dist;
	t_vect2		ln_start;
	t_vect2		ln_end;
	double		angle;
	t_vars		*vars;
	int			ln_height;
	int			clr;
	int			x;

	vars = (t_vars *)param;
	x = 0;
	// ft_memset(vars->canvas->pixels, 0, WIDTH * HEIGHT * sizeof(int));
	while (x < WIDTH)
	{
		angle = (double)x / WIDTH * FOV - FOV / 2;
		dist = cast_ray(&vars->map, &vars->player, vec_rot(vars->player.dir, angle));
		if (dist.x < dist.y)
		{
			ln_height = (int)WIDTH / dist.x;
			clr = 0xff0000ff;
		}
		else
		{
			ln_height = (int)WIDTH / dist.y;
			clr = 0x0000ffff;
		}
		// ln_height = ln_height / sin(M_PI_2) * sin(vec_angle(vec_rot(vars->player.dir, angle), vec(0.0, 1.0)));
		ln_start.x = x;
		ln_start.y = -ln_height / 2 + HEIGHT / 2;
		if (ln_start.y < 0)
			ln_start.y = 0;
		ln_end.x = x;
		ln_end.y = ln_height / 2 + HEIGHT / 2;
		if (ln_end.y >= HEIGHT)
			ln_end.y = HEIGHT - 1;
		line(ln_start, ln_end, clr, vars);
		x++;
	}
}
