/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/15 21:50:10 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/20 19:27:19 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "libft.h"
#include "cub3d.h"

static void	st_draw_walls(t_vars *vars, double *z_arr)
{
	uint32_t	x;
	double		angle;

	x = 0;
	angle = 0.0;
	while (x < WIDTH)
	{
		angle = (double)x / WIDTH * FOV - FOV / 2;
		vars->dst = cast_ray(&vars->map, &vars->player, \
			vec_rot(vars->player.dir, angle));
		if (vars->dst.x < vars->dst.y)
			z_arr[x] = vars->dst.x;
		else
			z_arr[x] = vars->dst.y;
		draw_line(vars, x, angle);
		x++;
	}
}

void	render(void *param)
{
	t_vars		*vars;
	double		z_arr[WIDTH];

	vars = (t_vars *)param;
	ft_memset(vars->canvas->pixels, 0, WIDTH * HEIGHT * \
		sizeof(uint32_t) / 2);
	ft_memset(vars->canvas->pixels + WIDTH * HEIGHT * sizeof(uint32_t) / 2, \
		128, WIDTH * HEIGHT * sizeof(uint32_t) / 2);
	st_draw_walls(vars, z_arr);
	sprite_display(vars, z_arr);
	printf("pos x %f pos y %f\n", vars->player.pos.x, vars->player.pos.y);
}
