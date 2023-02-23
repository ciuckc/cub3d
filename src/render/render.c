/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:54 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/23 17:46:44 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "libft.h"
#include "cub3d.h"

static void	st_draw_wall(t_vars *vars, double *z_arr)
{
	uint32_t	x;
	double		angle;
	t_fvect2	pos[3];
	t_fvect2	ray_dir;

	x = 0;
	angle = 0.0;
	ray_dir = (t_fvect2){0};
	while (x < WIDTH)
	{
		angle = (double)x / WIDTH * FOV - FOV / 2;
		ray_dir = vec_rot(vars->player.dir, angle);
		vars->dst = cast_ray(&vars->map, &vars->player, ray_dir);
		z_arr[x] = vars->dst.y;
		if (vars->dst.x < vars->dst.y)
			z_arr[x] = vars->dst.x;
		draw_line(vars, x, angle, pos);
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
	ft_memset(vars->canvas->pixels + WIDTH * HEIGHT * \
	sizeof(uint32_t) / 2, 128, WIDTH * HEIGHT * \
		sizeof(uint32_t) / 2);
	draw_floor(vars);
	st_draw_wall(vars, z_arr);
	sprite_display(vars, z_arr);
}
