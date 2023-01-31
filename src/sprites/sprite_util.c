/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:05:34 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/31 16:03:08 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	sprt->pos.y = 4.5;
}

void	sprite_put_pixel(t_vars *vars, t_vect2 i, t_vect2 img_i, t_sprite *spr)
{
	if (get_pixel(spr->tex, img_i) & 0xffffff00)
		mlx_put_pixel(vars->canvas, i.x, i.y, get_pixel(spr->tex, img_i));
}
