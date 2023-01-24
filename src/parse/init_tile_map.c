/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_tile_map.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 20:16:14 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/23 21:05:49 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tile	**init_tile_map(int32_t x, int32_t y)
{
	t_tile	**tiles;
	int32_t	i;

	tiles = ft_calloc(y, sizeof(t_tile *));
	if (tiles == NULL)
		exit_strerr(MALLOC_ERR);
	i = 0;
	while (i < y)
	{
		tiles[i] = ft_calloc(x, sizeof(t_tile));
		if (tiles[i] == NULL)
			exit_strerr(MALLOC_ERR);
		i++;
	}
	return (tiles);
}
