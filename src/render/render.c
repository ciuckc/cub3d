/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 13:24:59 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/03/16 17:19:46 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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

static void	st_draw_ceil(t_vars *vars)
{
	t_vect2	pos;

	pos = (t_vect2){.x = 0, .y = 0};
	while (pos.y < HEIGHT / 2)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			mlx_put_pixel(vars->canvas, pos.x, pos.y, \
			vars->ceil_clr);
			pos.x++;
		}
		pos.y++;
	}
}

static void	st_draw_floor(t_vars *vars)
{
	t_vect2	pos;

	pos = (t_vect2){.x = 0, .y = HEIGHT / 2};
	if (vars->texture[F] == NULL)
	{
		while (pos.y < HEIGHT)
		{
			pos.x = 0;
			while (pos.x < WIDTH)
			{
				mlx_put_pixel(vars->canvas, pos.x, pos.y, \
				vars->floor_clr);
				pos.x++;
			}
			pos.y++;
		}
	}
	else
		draw_floor(vars);
}

void	render(void *param)
{
	t_vars		*vars;
	double		z_arr[WIDTH];

	vars = (t_vars *)param;
	st_draw_floor(vars);
	st_draw_ceil(vars);
	st_draw_wall(vars, z_arr);
	sprite_display(vars, z_arr);
}
