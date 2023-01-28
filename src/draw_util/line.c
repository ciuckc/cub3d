/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:19:13 by mbatstra          #+#    #+#             */
/*   Updated: 2023/01/28 14:04:45 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"
#include "MLX42.h"

uint32_t	get_pixel(mlx_image_t *img, t_vect2 i)
{
	return (get_rgba(img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t)], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 1], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 2], \
				img->pixels[(i.x + i.y * img->width) * sizeof(uint32_t) + 3]));
}

// set inital diff and heading for line
static void	set_d_step(t_vect2 *d, t_vect2 *step, t_vect2 start, t_vect2 end)
{
	d->x = ft_abs(end.x - start.x);
	d->y = -ft_abs(end.y - start.y);
	if (start.x < end.x)
		step->x = 1;
	else
		step->x = -1;
	if (start.y < end.y)
		step->y = 1;
	else
		step->y = -1;
}

// bresenham algorithm look it up
// test if the true/break construction is really necessary
void	line(t_vect2 start, t_vect2 end, int clr, t_vars *vars)
{
	t_vect2	d;
	t_vect2	step;
	int		err;
	int		e2;

	set_d_step(&d, &step, start, end);
	err = d.x + d.y;
	while (true)
	{
		// make a wrapper that does this!!!
		if (start.x < WIDTH && start.y < HEIGHT && start.x > 0 && start.y > 0)
			mlx_put_pixel(vars->canvas, start.x, start.y, clr);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			start.x += step.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			start.y += step.y;
		}
	}
}
