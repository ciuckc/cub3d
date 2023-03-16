/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:10:19 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/16 13:16:54 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "parse.h"
#include "cub3d.h"

void	init_interact(t_vars *vars)
{
	mlx_texture_t	*tex;
	mlx_image_t		*int_img;
	mlx_t			*mlx;

	mlx = vars->mlx;
	tex = mlx_load_png(INTERACT_PATH);
	if (tex == NULL)
		exit_strerr(IMG_ERR);
	int_img = mlx_texture_to_image(mlx, tex);
	if (int_img == NULL)
		exit_strerr(IMG_ERR);
	mlx_delete_texture(tex);
	vars->texture2d[5] = int_img;
	mlx_image_to_window(vars->mlx, vars->texture2d[5], 0, 0);
	mlx_set_instance_depth(&vars->texture2d[5]->instances[0], Z_LVL_MINIMAP);
}
