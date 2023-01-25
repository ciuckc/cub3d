/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:17:05 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/14 13:17:33 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"

t_vect2	vec_round(t_fvect2 vec)
{
	t_vect2	result;

	result.x = round(vec.x);
	result.y = round(vec.y);
	return (result);
}

t_fvect2	vec_add(t_fvect2 v1, t_fvect2 v2)
{
	t_fvect2	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_fvect2	vec_mul(t_fvect2 vec, double factor)
{
	t_fvect2	result;

	result.x = vec.x * factor;
	result.y = vec.y * factor;
	return (result);
}

t_fvect2	vec_rot(t_fvect2 vec, double angle)
{
	t_fvect2	result;

	result.x = vec.x * cos(angle) - vec.y * sin(angle);
	result.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (result);
}
