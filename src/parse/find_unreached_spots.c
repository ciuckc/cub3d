/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_unreached_spots.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 03:27:23 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/20 03:53:45 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_vect2	*st_new_vect(int x, int y)
{
	t_vect2	*new;

	new = ft_calloc(1, sizeof(t_vect2));
	if (new == NULL)
		exit_strerr(MALLOC_ERR);
	*new = (t_vect2){x, y};
	return (new);
}

t_vect2	*find_unreached_spots(t_tile **map, t_vect2 m_size)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < m_size.y)
	{
		x = 0;
		while (x < m_size.x)
		{
			if (!map[y][x].reached && map[y][x].type == FLOOR)
			{
				map[y][x].reached = true;
				return (st_new_vect(x, y));
			}
			x++;
		}
		y++;
	}
	return (NULL);
}