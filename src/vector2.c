/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:45:39 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/14 13:17:42 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

double	vec_len(t_fvect2 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
}

double	vec_dot(t_fvect2 v1, t_fvect2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	vec_angle(t_fvect2 v1, t_fvect2 v2)
{
	return (acos(vec_dot(v1, v2) / (vec_len(v1) * vec_len(v2))));
}

t_fvect2	vec(double x, double y)
{
	t_fvect2	result;

	result.x = x;
	result.y = y;
	return (result);
}
