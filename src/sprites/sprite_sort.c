/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:58:26 by mbatstra          #+#    #+#             */
/*   Updated: 2023/02/24 17:21:57 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "libft.h"
#include "cub3d.h"

void	st_swap(t_sprite *i, t_sprite *j)
{
	t_sprite	swp;

	swp = *i;
	*i = *j;
	*j = swp;
}

bool	st_is_closer(t_sprite sp1, t_sprite sp2, t_fvect2 player)
{
	double	dist1;
	double	dist2;

	dist1 = vec_len(vec(sp1.pos.x - player.x, sp1.pos.y - player.y));
	dist2 = vec_len(vec(sp2.pos.x - player.x, sp2.pos.y - player.y));
	return (dist1 < dist2);
}

int32_t	st_part(t_sprite *arr, int32_t lo, int32_t hi, t_fvect2 player)
{
	t_sprite	piv;
	int32_t		i;
	int32_t		j;

	piv = arr[hi];
	i = lo - 1;
	j = lo;
	while (j < hi)
	{
		if (st_is_closer(piv, arr[j], player))
		{
			i++;
			st_swap(&arr[i], &arr[j]);
		}
		j++;
	}
	st_swap(&arr[i + 1], &arr[hi]);
	return (i + 1);
}

void	st_qsort(t_sprite *arr, int32_t lo, int32_t hi, t_fvect2 player)
{
	int32_t	st_part_i;

	if (lo >= hi)
		return ;
	st_part_i = st_part(arr, lo, hi, player);
	st_qsort(arr, lo, st_part_i - 1, player);
	st_qsort(arr, st_part_i + 1, hi, player);
}

void	sprites_sort(t_vars *vars)
{
	st_qsort(vars->sprite, 0, vars->num_sprites - 1, vars->player.pos);
}
