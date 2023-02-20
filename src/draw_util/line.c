/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 18:19:13 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/20 18:52:35 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "cub3d.h"
#include "MLX42.h"

// bresenham algorithm look it up
// test if the true/break construction is really necessary
void	line(t_vect2 start, t_vect2 end, uint32_t *clr, t_vars *vars)
{
	uint32_t	i;

	i = 0;
	while (start.y < end.y)
	{
		mlx_put_pixel(vars->canvas, start.x, start.y, clr[i]);
		i++;
		start.y++;
	}
}
