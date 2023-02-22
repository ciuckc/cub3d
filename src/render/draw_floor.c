/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 00:49:56 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/22 02:19:41 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	st_draw_row(uint32_t y, t_vars *vars, t_fvect2 *pos, t_fvect2 step, \
	mlx_image_t *img)
{
	uint32_t	x;
	t_vect2		cell;
	t_vect2		tex_pos;

	x = 0;
	cell = (t_vect2){0};
	tex_pos = (t_vect2){0};
	while (x < WIDTH)
	{
		cell = (t_vect2){(int)pos->x, (int)pos->y};
		tex_pos = (t_vect2){(int)(img->width * (pos->x - cell.x)) & \
			(img->width - 1), (int)(img->height * (pos->y - cell.y)) & \
			(img->height - 1)};
		pos->x += step.x;
		pos->y += step.y;
		mlx_put_pixel(vars->canvas, x, y, get_pixel(img, tex_pos));
		x++;
	}
}

void	draw_floor(t_vars *vars)
{
	uint32_t	y;
	double		row_dist;
	t_fvect2	*raydir;
	t_fvect2	flr[2];
	mlx_image_t	*img;

	img = vars->texture[N];
	y = HEIGHT / 2 + 1;
	raydir = (t_fvect2 [2]){(t_fvect2){0}, (t_fvect2){0}};
	while (y < HEIGHT)
	{
		raydir[0] = vec_rot(vars->player.dir, -FOV / 2);
		raydir[1] = vec_rot(vars->player.dir, FOV - FOV / 2);
		row_dist = (0.5 * HEIGHT) / (y - HEIGHT / 2);
		flr[0] = (t_fvect2){row_dist * (raydir[1].x - raydir[0].x) / WIDTH, \
			row_dist * (raydir[1].y - raydir[0].y) / WIDTH};
		flr[1] = (t_fvect2){vars->player.pos.x + row_dist * raydir[0].x, \
			vars->player.pos.y + row_dist * raydir[1].y};
		st_draw_row(y, vars, &flr[1], flr[0], img);
		y++;
	}
}
