/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reach_neighbours.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 22:01:25 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/20 03:17:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	reach_neighbours(t_tile **map, t_list *queue)
{
	uint8_t	i;
	t_vect2	v;
	t_vect2	*table;

	i = 1;
	table = (t_vect2 [9]){[UP] = {.y = -1, .x = 0}, [RIGHT] = {.y = 0, .x = 1}, \
	[DOWN] = {.y = 1, .x = 0}, [LEFT] = {.y = 0, .x = -1}};
	v = *(t_vect2 *)queue->content;
	while (i <= 8)
	{
		if (map[v.y + table[i].y][v.x + table[i].x].reached != true)
		{
			map[v.y + table[i].y][v.x + table[i].x].reached = true;
			map[v.y][v.x].frontier_neighbour |= i;
		}
		i <<= 1;
	}
}
