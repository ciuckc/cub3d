/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 00:49:56 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/15 14:28:21 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math.h"

static void	st_draw_row(uint32_t y, t_vars *vars, t_fvect2 *flr, \
	double row_dist)
{
	uint32_t	x;
	t_vect2		cell;
	t_vect2		tex_pos;
	mlx_image_t	*img;

	x = 0;
	img = vars->texture[N];
	cell = (t_vect2){0};
	tex_pos = (t_vect2){0};
	while (x < WIDTH)
	{
		cell = (t_vect2){floor(flr[1].x), floor(flr[1].y)};
		tex_pos = (t_vect2){(int)(img->width * (flr[1].x - cell.x)) & \
			(img->width - 1), (int)(img->height * (flr[1].y - cell.y)) & \
			(img->height - 1)};
		flr[1].x += flr[0].x;
		flr[1].y += flr[0].y;
		mlx_put_pixel(vars->canvas, x, y, apply_shade(get_pixel(img, tex_pos), \
			row_dist));
		x++;
	}
}

void	draw_floor(t_vars *vars)
{
	uint32_t	y;
	double		row_dist;
	t_fvect2	*raydir;
	t_fvect2	flr[2];

	y = HEIGHT / 2 + 1;
	raydir = (t_fvect2 [2]){(t_fvect2){0}, (t_fvect2){0}};
	raydir[0] = vec_mul(vec_rot(vars->player.dir, -FOV / 2.0), 1.156);
	raydir[1] = vec_mul(vec_rot(vars->player.dir, FOV / 2.0), 1.156);
	while (y < HEIGHT)
	{
		row_dist = (0.5 * HEIGHT) / (y - HEIGHT * 0.5);
		flr[0] = (t_fvect2){row_dist * (raydir[1].x - raydir[0].x) / WIDTH, \
			row_dist * (raydir[1].y - raydir[0].y) / WIDTH};
		flr[1] = (t_fvect2){vars->player.pos.x + row_dist * raydir[0].x, \
			vars->player.pos.y + row_dist * raydir[0].y};
		st_draw_row(y, vars, flr, row_dist);
		y++;
	}
}
