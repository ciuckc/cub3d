/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_from_pos.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 00:50:16 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/16 18:54:11 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	st_pop(t_list **queue)
{
	t_list	*prev;

	prev = *queue;
	if ((*queue)->next != NULL)
	{
		*queue = (*queue)->next;
		free(prev->content);
		free(prev);
	}
	else
	{
		free((*queue)->content);
		free(*queue);
		*queue = NULL;
	}
}

static bool	st_invalid_map_pos(t_vect2 curr_pos, t_vect2 m_size, \
t_tile **tile_map)
{
	if (curr_pos.x == m_size.x - 1 || curr_pos.x == 0 || curr_pos.y == 0 \
	|| curr_pos.y == m_size.y - 1)
		return (true);
	else if (tile_map[curr_pos.y][curr_pos.x].type == UNREACH)
		return (true);
	else
		return (false);
}

void	fill_from_pos(t_tile **tile_map, t_list *queue, t_vect2 m_size)
{
	t_vect2	*curr_pos;

	while (true)
	{
		curr_pos = queue->content;
		if (st_invalid_map_pos(*curr_pos, m_size, tile_map))
			exit_strerr(INV_WALL_ERR);
		reach_neighbours(tile_map, queue);
		add_neighbours_to_queue(tile_map, queue);
		st_pop(&queue);
		if (queue == NULL)
			break ;
	}
}
