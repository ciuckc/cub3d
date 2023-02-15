/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_img_vert_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/28 19:02:19 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/15 20:48:13 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parse.h"
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

static double	st_get_wall_x(t_vars *vars, t_fvect2 dst, t_fvect2 ray_dir)
{
	double	wall_x;

	if (dst.x < dst.y)
		wall_x = vars->player.pos.y + dst.x * ray_dir.y;
	else
		wall_x = vars->player.pos.x + dst.y * ray_dir.x;
	wall_x -= floorf(wall_x);
	return (wall_x);
}

static uint32_t	*st_init_pixel_arr(uint32_t ln_height)
{
	uint32_t	*pixel_arr;

	if (ln_height > HEIGHT)
		ln_height = HEIGHT;
	pixel_arr = ft_calloc(ln_height, ln_height);
	if (pixel_arr == NULL)
		exit_strerr(MALLOC_ERR);
	return (pixel_arr);
}

static void	st_put_pixels(mlx_image_t *img, uint32_t *pixel_arr, \
	uint32_t ln_height, uint32_t texture_x)
{
	uint32_t	i;
	uint32_t	texture_y;
	uint32_t	step;
	uint32_t	offset;

	i = 0;
	step = img->height / ln_height;
	offset = (ln_height - HEIGHT) / 2;
	texture_y = offset * step;
	if (ln_height > HEIGHT)
		ln_height = HEIGHT;
	while (i < ln_height)
	{
		pixel_arr[i] = img->pixels[step * texture_y + texture_x];
		texture_y += step;
		i++;
	}
}

uint32_t	*get_img_vert_array(t_vars *vars, t_fvect2 dst, t_fvect2 ray_dir, \
	uint32_t ln_height)
{
	mlx_image_t	*img;
	uint32_t	*pixel_arr;

	img = st_get_cardinal_img(vars, dst, ray_dir);
	pixel_arr = st_init_pixel_arr(ln_height);
	st_put_pixels(img, pixel_arr, ln_height, img->width * \
		st_get_wall_x(vars, dst, ray_dir));
	return (pixel_arr);
}
