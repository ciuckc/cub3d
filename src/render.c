/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:54 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/24 17:33:59 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <limits.h>
#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

// shift line segment to middle of screen
// clamp height if it's negative or bigger than screen height
// running into walls at straight angles makes ln_height overflow
// find a better solution!!!
static void	st_display_line(void *param, int x, int ln_height, int clr)
{
	t_vect2		ln_start;
	t_vect2		ln_end;
	t_vars		*vars;

	if (ln_height == INT_MIN)
		ln_height = HEIGHT;
	vars = (t_vars *)param;
	ln_start.x = x;
	ln_start.y = -ln_height / 2 + HEIGHT / 2;
	if (ln_start.y < 0)
		ln_start.y = 0;
	ln_end.x = x;
	ln_end.y = ln_height / 2 + HEIGHT / 2;
	if (ln_end.y >= HEIGHT)
		ln_end.y = HEIGHT;
	line(ln_start, ln_end, clr, vars);
}

// angle is relative to player direction 
// so it can easily be used for fisheye correction
// cos(angle) is simplified form of
// sin(M_PI_2 - angle) / sin(M_PI_2);
// by having both x and y rays we know if hit was NS or EW
// later we might have to use part of the raycaster 
// to figure out what single direction the hit was (eg. N, W, S or E) 
static void	st_get_height(t_vars *vars, int x, int *ln_height, int *clr)
{
	t_fvect2	dst;
	double		angle;

	angle = (double)x / WIDTH * FOV - FOV / 2;
	dst = cast_ray(&vars->map, &vars->player, vec_rot(vars->player.dir, angle));
	if (dst.x < dst.y)
	{
		dst.x *= cos(angle);
		*ln_height = (int)HEIGHT / dst.x;
		*clr = 0x80652bff;
	}
	else
	{
		dst.y *= cos(angle);
		*ln_height = (int)HEIGHT / dst.y;
		*clr = 0xb08e45ff;
	}
}

// clear canvas for new frame
// iterate over each pixel column in window
void	render(void *param)
{
	t_vars	*vars;
	int		ln_height;
	int		clr;
	int		x;

	vars = (t_vars *)param;
	ft_memset(vars->canvas->pixels, 0, WIDTH * HEIGHT * sizeof(int) / 2);
	ft_memset(vars->canvas->pixels + WIDTH * HEIGHT * sizeof(int) / 2, \
				128, WIDTH * HEIGHT * sizeof(int) / 2);
	x = 0;
	while (x < WIDTH)
	{
		st_get_height(vars, x, &ln_height, &clr);
		st_display_line(param, x, ln_height, clr);
		x++;
	}
}
