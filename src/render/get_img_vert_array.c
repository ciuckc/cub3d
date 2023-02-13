/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_img_vert_array.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/28 19:02:19 by scristia      #+#    #+#                 */
/*   Updated: 2023/02/02 17:21:44 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t	*st_get_pos_text(t_vars *vars, t_fvect2 dst)
{
	mlx_image_t	*img;

	if (dst.x < dst.y)
	{
		if (dst.x > 0)
			img = vars->texture[E];
		else
			img = vars->texture[W];
	}
	else
	{
		if (dst.y > 0)
			img = vars->texture[S];
		else
			img = vars->texture[N];
	}
	return (img);
}

uint32_t	*get_img_vert_array(t_vars *vars, t_fvect2 dst, t_fvect2 ray_dir)
{
	mlx_image_t	*img;
	t_fvect2	end_hit;

	(void)ray_dir;
	end_hit = (t_fvect2){vars->player.pos.x + dst.x, vars->player.pos.y + \
	dst.y};
	img = st_get_pos_text(vars, dst);
	return (NULL);
}
