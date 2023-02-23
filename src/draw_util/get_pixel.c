/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 18:59:13 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/23 17:46:32 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	apply_shade(uint32_t clr, double dist)
{
	double	intensity;

	intensity = 1 / dist * 0.6;
	if (intensity == 1)
		return (clr);
	clr = get_rgba(get_red(clr) * intensity, get_grn(clr) * intensity, \
		get_blu(clr) * intensity, get_alpha(clr));
	return (clr);
}

uint32_t	get_pixel(mlx_image_t *img, t_vect2 i)
{
	return (get_rgba(img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t)], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 1], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 2], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 3]));
}

uint32_t	inv_color(uint32_t clr)
{
	uint32_t	inv;

	inv = 0;
	inv |= (255 - (clr >> 24 & 0xff)) << 24;
	inv |= (255 - (clr >> 16 & 0xff)) << 16;
	inv |= (255 - (clr >> 8 & 0xff)) << 8;
	inv |= 0xff;
	return (inv);
}
