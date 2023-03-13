/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/22 00:49:56 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/13 21:27:48 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "math.h"

static void	st_draw_row(uint32_t y, t_vars *vars, t_fvect2 *pos, t_fvect2 step, \
	mlx_image_t *img, double row_dist)
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
		tex_pos = (t_vect2){(int)(img->width * (pos->x - cell.x)) % \
			(img->width - 1), (int)(img->height * (pos->y - cell.y)) % \
			(img->height - 1)};
		pos->x += step.x;
		pos->y += step.y;
		mlx_put_pixel(vars->canvas, x, y, apply_shade(get_pixel(img, tex_pos), row_dist));
		x++;
	}
}

void	draw_floor(t_vars *vars)
{
	uint32_t	y;
	double		row_dist;
	t_fvect2	*raydir;
	t_fvect2	flr[3];

	// xpm_t *xpm = mlx_load_xpm42("assets/test.xpm42");
	// xpm_t *xpm = mlx_load_xpm42("assets/floorsmall.xpm42");
	xpm_t *xpm = mlx_load_xpm42("assets/floor.xpm42");
	mlx_image_t *img = mlx_texture_to_image(vars->mlx, &xpm->texture);

	y = HEIGHT / 2 + 1;
	flr[2] = vec_mul(vec_rot(vars->player.dir, M_PI_2), 0.58);
	raydir = (t_fvect2 [2]){(t_fvect2){0}, (t_fvect2){0}};
	raydir[0] = vec_sub(vars->player.dir, flr[2]);
	raydir[1] = vec_add(vars->player.dir, flr[2]);

	raydir[0] = vec_mul(vec_rot(vars->player.dir, -FOV / 2.0), 1.156);
	raydir[1] = vec_mul(vec_rot(vars->player.dir, FOV / 2.0), 1.156); 

	while (y < HEIGHT)
	{
		row_dist = (0.5 * HEIGHT) / (y - HEIGHT * 0.5);
		flr[0] = (t_fvect2){row_dist * (raydir[1].x - raydir[0].x) / WIDTH, \
			row_dist * (raydir[1].y - raydir[0].y) / WIDTH};
		flr[1] = (t_fvect2){vars->player.pos.x + row_dist * raydir[0].x, \
			vars->player.pos.y + row_dist * raydir[0].y};
		st_draw_row(y, vars, &flr[1], flr[0], img, row_dist);
		y++;
	}
}
