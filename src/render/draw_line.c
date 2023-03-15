/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 17:59:20 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/13 17:22:54 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math.h"
#include <stdio.h>

static mlx_image_t	*st_get_cardinal_img(t_vars *vars, t_fvect2 dst, t_fvect2 \
ray_dir)
{
	mlx_image_t	*img;

	if (dst.x < dst.y)
	{
		if (vars->player.pos.x + dst.y * ray_dir.x > vars->player.pos.x)
			img = vars->texture[E];
		else
			img = vars->texture[W];
	}
	else
	{
		if (vars->player.pos.y + dst.x * ray_dir.y > vars->player.pos.y)
			img = vars->texture[S];
		else
			img = vars->texture[N];
	}
	return (img);
}

static void	st_set_img_pos(mlx_image_t *img, t_fvect2 *coords, \
int32_t ln_height, double wall_x)
{
	double	step;
	double	offset;

	coords[LN_START].y = -ln_height / 2 + HEIGHT / 2;
	if (coords[LN_START].y < 0)
		coords[LN_START].y = 0;
	coords[LN_END].y = ln_height / 2 + HEIGHT / 2;
	if (coords[LN_END].y >= HEIGHT)
		coords[LN_END].y = HEIGHT;
	step = (double)img->height / ln_height;
	offset = coords[LN_START].y - HEIGHT / 2 + ln_height / 2;
	coords[IMG_POS].x = floor(wall_x * (double)img->width);
	coords[IMG_POS].y = offset * step;
}

static void	st_put_pixels(t_vars *vars, mlx_image_t *img, t_fvect2 *coords, \
	float img_step)
{
	uint32_t	clr;
	double		short_dist;

	clr = 0;
	while (coords[LN_START].y < coords[LN_END].y)
	{
		if (vars->dst.x < vars->dst.y)
			short_dist = vars->dst.x;
		else
			short_dist = vars->dst.y;
		clr = apply_shade(get_pixel(img, (t_vect2){(int)coords[IMG_POS].x, \
		(int)coords[IMG_POS].y}), short_dist);
		mlx_put_pixel(vars->canvas, coords[LN_START].x, coords[LN_START].y, \
			clr);
		coords[IMG_POS].y += img_step;
		coords[LN_START].y++;
	}
}

static double	st_set_wallx_ln_height(t_vars *vars, double angle, \
	t_fvect2 ray_dir, int32_t *ln_height)
{
	double	wall_x;

	if (vars->dst.x < vars->dst.y)
	{
		vars->dst.x *= cos(angle);
		*ln_height = HEIGHT / vars->dst.x;
		vars->dst.x /= cos(angle);
		wall_x = vars->player.pos.y + vars->dst.x * ray_dir.y;
	}
	else
	{
		vars->dst.y *= cos(angle);
		*ln_height = HEIGHT / vars->dst.y;
		vars->dst.y /= cos(angle);
		wall_x = vars->player.pos.x + vars->dst.y * ray_dir.x;
	}
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	draw_line(t_vars *vars, uint32_t x, double angle, t_fvect2 \
	*pos)
{
	mlx_image_t	*img;
	t_fvect2	ray_dir;
	int32_t		ln_height;
	double		wall_x;

	ray_dir = vec_rot(vars->player.dir, angle);
	img = st_get_cardinal_img(vars, vars->dst, ray_dir);
	wall_x = st_set_wallx_ln_height(vars, angle, ray_dir, &ln_height);
	st_set_img_pos(img, pos, ln_height, wall_x);
	pos[LN_START].x = x;
	pos[LN_END].x = x;
	st_put_pixels(vars, img, pos, (double)img->height / ln_height);
}
