/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_img_vert_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/28 19:02:19 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/15 17:33:44 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <stdio.h>

static mlx_image_t	*st_get_cardinal_img(t_vars *vars, t_fvect2 dst, \
t_fvect2 ray_dir)
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

static uint32_t	*st_init_line_buff(mlx_image_t *img, double wall_x, \
	int32_t ln_height)
{
	uint32_t	texture_x;
	uint32_t	texture_y;

	(void)ln_height;
	texture_x = wall_x * img->width;
	texture_y = 0;
	return (NULL);
}

uint32_t	*get_img_vert_array(t_vars *vars, t_fvect2 dst, t_fvect2 ray_dir, \
	int32_t ln_height)
{
	mlx_image_t	*img;
	double		wall_x;

	img = st_get_cardinal_img(vars, dst, ray_dir);
	if (dst.x < dst.y)
		wall_x = vars->player.pos.y + dst.x * ray_dir.y;
	else
		wall_x = vars->player.pos.x + dst.y * ray_dir.x;
	wall_x -= floorf(wall_x);
	st_init_line_buff(img, wall_x, ln_height);
	return (NULL);
}
