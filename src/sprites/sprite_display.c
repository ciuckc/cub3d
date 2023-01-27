/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:05:34 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/27 19:13:01 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42.h"
#include "parse.h"
#include "libft.h"
#include "cub3d.h"

void	sprite_init(t_vars *vars, t_sprite *sprt, char *path)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(path);
	if (xpm == NULL)
		exit_strerr(MALLOC_ERR);
	sprt->tex = mlx_texture_to_image(vars->mlx, &xpm->texture);
	if (sprt->tex == NULL)
		exit_strerr(MALLOC_ERR);
	sprt->pos.x = 30; 
	sprt->pos.y = 2; 
}

// calculate the sprite coords relative to the player
// multiply those coords by the inverse of the camera matrix
// to get the transformed sprite coords
t_fvect2	get_transform_coord(t_vars *vars)
{
	t_fvect2	transform;
	t_fvect2	cam_plane;
	t_fvect2	rel_pos;
	t_player	*player;
	t_sprite	*sprite;
	double 		inv_det;

	player = &vars->player;
	sprite = &vars->sprite;
	rel_pos.x = sprite->pos.x - player->pos.x;
	rel_pos.y = sprite->pos.y - player->pos.y;
	cam_plane = vec_mul(vec_rot(player->dir, M_PI_2), 0.66);
	inv_det = 1.0 / (cam_plane.x * player->dir.y - player->dir.x * cam_plane.y);
	transform.x = inv_det * (player->dir.y * rel_pos.x - player->dir.x * rel_pos.y);
	transform.y = inv_det * (-cam_plane.y * rel_pos.x + cam_plane.x * rel_pos.y);
	return (transform);
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
    if(start->x < 0)
		start->x = 0;
    end->x = dim / 2 + x;
    if(end->x > WIDTH)
		end->x = WIDTH;
}

uint32_t	get_pixel(mlx_image_t *img, t_vect2 i)
{
	return (get_rgba(img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t)], \
					img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 1], \
					img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 2], \
					img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 3]));
}

void	sprite_display(t_vars *vars, double *z_arr)
{
	t_fvect2	transform;
	t_sprite	*sprite;
	uint32_t	clr;
	t_vect2		draw_start;
	t_vect2		draw_end;
	t_vect2		img_i;
	t_vect2		i;
	int32_t		sprite_dim;
	int32_t		sprite_x;
	int32_t		d;

	sprite = &vars->sprite;
	transform = get_transform_coord(vars);
	sprite_dim = fabs((int)HEIGHT / transform.y);
	sprite_x = (int)(WIDTH / 2) * (1 + transform.x / transform.y);
	set_draw_lim(&draw_start, &draw_end, sprite_dim, sprite_x);
	i.x = draw_start.x;
	while (i.x < draw_end.x)
	{
		img_i.x = (int)((i.x - (-sprite_dim / 2 + sprite_x)) * sprite->tex->width / sprite_dim);
		i.y = draw_start.y;
		if(transform.y > 0 && i.x > 0 && i.x < WIDTH && transform.y < z_arr[i.x])
        	while (i.y < draw_end.y)
			{
        	  d = i.y * 256 - HEIGHT * 128 + sprite_dim * 128;
			  img_i.y = d * sprite->tex->height / sprite_dim / 256;
			  clr = get_pixel(sprite->tex, img_i);
			  if (clr & 0xffffff00)
			  	mlx_put_pixel(vars->canvas, i.x, i.y, clr);
			  i.y++;
        	}
		i.x++;
	}
}
