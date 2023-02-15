/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 16:18:54 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/15 17:34:11 by scristia      ########   odam.nl         */
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
static void	st_display_line(t_vars *vars, uint32_t x, \
							int32_t ln_height, uint32_t clr)
{
	t_vect2		ln_start;
	t_vect2		ln_end;

	if (ln_height == INT_MIN)
		ln_height = HEIGHT;
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
static double	st_get_dist(t_vars *vars, uint32_t x, \
							int32_t *ln_height, uint32_t *clr)
{
	double		angle;
	t_fvect2	dst;
	t_fvect2	ray_dir;

	angle = (double)x / WIDTH * FOV - FOV / 2;
	ray_dir = vec_rot(vars->player.dir, angle);
	dst = cast_ray(&vars->map, &vars->player, ray_dir);
	if (dst.x < dst.y)
	{
		dst.x *= cos(angle);
		if (dst.x < MOV_SPD)
			dst.x = MOV_SPD;
		*ln_height = (int32_t)HEIGHT / dst.x;
		get_img_vert_array(vars, dst, ray_dir, *ln_height);
		*clr = 0x80652bff;
		return (dst.x);
	}
	dst.y *= cos(angle);
	if (dst.y < MOV_SPD)
		dst.y = MOV_SPD;
	*ln_height = (int32_t)HEIGHT / dst.y;
	get_img_vert_array(vars, dst, ray_dir, *ln_height);
	*clr = 0xb08e45ff;
	return (dst.y);
}

static void	st_draw_floor_ceil(t_vars *vars)
{
	ft_memset(vars->canvas->pixels, vars->ceil_clr, WIDTH * HEIGHT * \
		sizeof(uint32_t) / 2);
	ft_memset(vars->canvas->pixels + WIDTH * HEIGHT * sizeof(uint32_t) / 2, \
		vars->floor_clr, WIDTH * HEIGHT * sizeof(uint32_t) / 2);
}

static void	st_draw_walls(t_vars *vars, double *z_arr)
{
	uint32_t	clr;
	uint32_t	x;
	int32_t		ln_height;

	x = 0;
	while (x < WIDTH)
	{
		z_arr[x] = st_get_dist(vars, x, &ln_height, &clr);
		st_display_line(vars, x, ln_height, clr);
		x++;
	}
}

// clear canvas for new frame
// iterate over each pixel column in window
void	render(void *param)
{
	t_vars		*vars;
	double		z_arr[WIDTH];

	vars = (t_vars *)param;
	st_draw_floor_ceil(vars);
	st_draw_walls(vars, z_arr);
	sprite_display(vars, z_arr);
}
