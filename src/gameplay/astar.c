/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:25:07 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/03 18:19:58 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"
#include "libft.h"
#include "parse.h"

typedef struct s_astar {
	struct s_astar	*prev;
	t_vect2				pos;
	double				dist_score;
	double				heur_score;
}			t_astar;

void	st_init_node(t_astar *node, t_vect2 pos)
{
	node->prev = NULL;
	node->dist_score = 1e30;
	node->heur_score = 1e30;
	node->pos = pos;
}

t_astar	*st_init_arr(t_map *map)
{
	t_astar	*arr;
	t_vect2			i;

	arr = (t_astar *)malloc(map->size.x * map->size.y * sizeof(t_astar));
	if (arr == NULL)
		exit_strerr(MALLOC_ERR);
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			st_init_node(&arr[i.x + i.y * map->size.x], i);
			i.x++;
		}
		i.y++;
	}
	return (arr);
}

double	st_heuristic(t_fvect2 end, t_fvect2 current)
{
	return (hypot(end.x - current.x, end.y - current.y));
}

void	st_insert_node(t_list **list, t_list *node)
{
	t_list	*temp;

	temp = *list;
	if (temp == NULL)
		return ;
	while (temp->next != NULL && ((t_astar *)temp->content)->heur_score < \
								((t_astar *)node->content)->heur_score)
		temp = temp->next;
	if (temp->content == node->content)
		return ;
	if (temp->next == NULL)
	{
		temp->next = node;
		node->next = NULL;
	}
	else
	{
		node->next = temp->next->next;
		temp->next = node;
	}
}

t_list	*st_get_neighbors(t_astar *arr, t_astar *current, t_map *map)
{
	t_vect2	pos;
	t_list	*lst;

	lst = NULL;
	pos = current->pos;
	if (pos.x > 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[(pos.x - 1) + pos.y * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.x < map->size.x - 2)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[(pos.x + 1) + pos.y * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.y > 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[pos.x + (pos.y - 1) * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.y < map->size.y - 2)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[pos.x + (pos.y + 1) * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	return (lst);
}

void	st_iter_neighbors(t_astar *arr, t_astar *current, t_list **open, t_vect2 end, t_map *map)
{
	t_astar *temp;	
	double	new_dscore;
	t_list	*neighbors;
	t_list	*node;
	t_list	*next;

	neighbors = st_get_neighbors(arr, current, map);
	node = neighbors;
	new_dscore = current->dist_score + 1;
	while (node != NULL)
	{
		temp = (t_astar *)node->content;
		if (new_dscore < temp->dist_score)
		{
			temp->prev = current;
			temp->dist_score = new_dscore;
			temp->heur_score = new_dscore + st_heuristic(vec(temp->pos.x, temp->pos.y), vec(end.x, end.y));
			next = node->next;
			st_insert_node(open, node);
		}
		node = next;
	}
}

t_list	**astar(t_vect2 start, t_vect2 end, t_map *map)
{
	t_astar	*arr;
	t_astar	current;
	t_list	*open;
	t_list	*temp;
	t_list	*closed;

	arr = st_init_arr(map);
	arr[start.x + start.y * map->size.x].dist_score = 0;
	arr[start.x + start.y * map->size.x].heur_score = st_heuristic(vec(start.x ,start.y), vec(end.x, end.y));
	open = ft_lstnew(&arr[start.x + start.y * map->size.x]);
	if (open == NULL)
		exit_strerr(MALLOC_ERR);
	while (open != NULL)
	{
		current = *((t_astar *)(open->content));
		if (current.pos.x == end.x && current.pos.y == end.y)
		{
			printf("yes!\n");
			return (NULL);
			// return (st_get_path(closed, current));
		}
		st_iter_neighbors(arr, &current, &open, end, map);
		temp = open;
		open = open->next;
		temp->next = closed;
		closed = temp;
	}
	return (NULL);
}
