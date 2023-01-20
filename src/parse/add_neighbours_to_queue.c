/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_neighbours_to_queue.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 00:15:43 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/20 03:14:08 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_list	*st_new_queue_node(t_vect2 *table, t_vect2 v, uint8_t dir)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (new == NULL)
		exit_strerr(MALLOC_ERR);
	new->content = (t_vect2 *)ft_calloc(1, sizeof(t_vect2));
	if (new->content == NULL)
		exit_strerr(MALLOC_ERR);
	*(t_vect2 *)new->content = (t_vect2){.y = v.y + table[dir].y, \
		.x = v.x + table[dir].x};
	return (new);
}

void	add_neighbours_to_queue(t_tile **map, t_list *queue)
{
	uint8_t	dir;
	t_vect2	v;
	t_vect2	*table;
	t_list	*new;

	dir = 1;
	table = (t_vect2 [9]){[UP] = {.y = -1, .x = 0}, [RIGHT] = {.y = 0, .x = 1}, \
	[DOWN] = {.y = 1, .x = 0}, [LEFT] = {.y = 0, .x = -1}};
	v = *(t_vect2 *)queue->content;
	while (dir <= 8)
	{
		if (map[v.y][v.x].frontier_neighbour & dir)
		{
			new = st_new_queue_node(table, v, dir);
			ft_lstadd_back(&queue, new);
		}
		dir <<= 1;
	}
}
