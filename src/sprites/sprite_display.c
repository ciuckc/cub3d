/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:05:34 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/31 15:57:54 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

// calculate the sprite coords relative to the player
// multiply those coords by the inverse of the camera matrix
// to get the transformed sprite coords
// the camera plane gets it's length through the following equation:
// 2 * atan(plane_len / dir_len) = fov
// or
// plane_len = tan(fov / 2) = 0.58
t_fvect2	get_transform_coord(t_vars *vars, t_sprite *sprite)
{
	t_fvect2	cam_plane;
	t_fvect2	pos;
	t_player	*player;
	double		inv_det;

	player = &vars->player;
	pos.x = sprite->pos.x - player->pos.x;
	pos.y = sprite->pos.y - player->pos.y;
	cam_plane = vec_mul(vec_rot(player->dir, M_PI_2), 0.58);
	inv_det = 1.0 / (cam_plane.x * player->dir.y - player->dir.x * cam_plane.y);
	return (vec(inv_det * (player->dir.y * pos.x - player->dir.x * pos.y), \
	inv_det * (-cam_plane.y * pos.x + cam_plane.x * pos.y)));
}

void	set_draw_lim(t_vect2 *start, t_vect2 *end, int32_t dim, int32_t x)
{
	start->y = -dim / 2 + HEIGHT / 2;
	if (start->y < 0)
		start->y = 0;
	end->y = dim / 2 + HEIGHT / 2;
	if (end->y > HEIGHT)
		end->y = HEIGHT;
	start->x = -dim / 2 + x;
	if (start->x < 0)
		start->x = 0;
	end->x = dim / 2 + x;
	if (end->x > WIDTH)
		end->x = WIDTH;
}

t_vect2	lerp_tex_coords(t_sprite *spr, t_vect2 spr_vars, t_vect2 i)
{
	t_vect2	img_i;

	img_i.x = (i.x - (-spr_vars.y / 2 + spr_vars.x)) * \
				spr->tex->width / spr_vars.y;
	img_i.y = (i.y * 2 - HEIGHT + spr_vars.y) * \
				spr->tex->height / spr_vars.y / 2;
	return (img_i);
}

void	sprite_drawcols(t_vars *vars, t_sprite *sprite, \
						t_vect2 spr_vars, double *z_arr)
{
	t_fvect2	transf;
	t_vect2		draw_start;
	t_vect2		draw_end;
	t_vect2		img_i;
	t_vect2		i;

	set_draw_lim(&draw_start, &draw_end, spr_vars.y, spr_vars.x);
	transf = get_transform_coord(vars, sprite);
	i.x = draw_start.x;
	while (i.x < draw_end.x)
	{
		i.y = draw_start.y;
		if (transf.y > 0 && i.x > 0 && i.x < WIDTH && transf.y < z_arr[i.x])
		{
			while (i.y < draw_end.y)
			{
				img_i = lerp_tex_coords(sprite, spr_vars, i);
				sprite_put_pixel(vars, i, img_i, sprite);
				i.y++;
			}
		}
		i.x++;
	}
}

void	sprite_display(t_vars *vars, double *z_arr)
{
	uint32_t	i;
	t_fvect2	transform;
	t_sprite	*sprite;
	t_vect2		spr_vars;

	i = 0;
	while (i < NUM_ENEMIES)
	{
		sprite = &vars->sprite[i];
		transform = get_transform_coord(vars, sprite);
		spr_vars.y = fabs((int)HEIGHT / transform.y);
		spr_vars.x = (int)((WIDTH / 2) * (1 + transform.x / transform.y));
		sprite_drawcols(vars, sprite, spr_vars, z_arr);
		i++;
	}
}
