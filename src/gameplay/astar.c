/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:25:07 by mbatstra          #+#    #+#             */
/*   Updated: 2023/03/07 19:52:38 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "cub3d.h"
#include "libft.h"
#include "parse.h"

void	st_init_node(t_astar *node, t_vect2 pos)
{
	node->prev = NULL;
	node->dist_score = 10e20;
	node->heur_score = 10e20;
	node->pos = pos;
}

void	st_freenodes(t_list *lst)
{
	t_list	*temp;

	if (lst == NULL)
		return ;
	temp = lst->next;
	while (temp != NULL)
	{
		free(lst);
		lst = temp;
		temp = temp->next;
	}
	free(lst);
}

void	st_init_arr(t_map *map, t_astar **arr)
{
	t_astar	*new;
	t_vect2	i;

	new = malloc(map->size.x * map->size.y * sizeof(t_astar));
	if (new == NULL)
		exit_strerr(MALLOC_ERR);
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			st_init_node(&new[i.x + i.y * map->size.x], i);
			i.x++;
		}
		i.y++;
	}
	*arr = new;
}

double	st_heuristic(t_fvect2 end, t_fvect2 current)
{
	return (hypot(end.x - current.x, end.y - current.y));
}

t_list	*st_get_neighbors(t_astar *arr, t_astar *current, t_map *map)
{
	t_vect2	pos;
	t_list	*lst;

	lst = NULL;
	pos = current->pos;
	if (pos.x > 0 && mapindex(map, pos.x - 1, pos.y) != WALL)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[(pos.x - 1) + pos.y * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.x < map->size.x - 1 && mapindex(map, pos.x + 1, pos.y) != WALL)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[(pos.x + 1) + pos.y * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.y > 0 && mapindex(map, pos.x, pos.y - 1) != WALL)
	{
		ft_lstadd_front(&lst, ft_lstnew(&arr[pos.x + (pos.y - 1) * map->size.x]));
		if (lst == NULL)
			exit_strerr(MALLOC_ERR);
	}
	if (pos.y < map->size.y - 1 && mapindex(map, pos.x, pos.y + 1) != WALL)
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

	// neighbors = st_get_neighbors(arr, current, map);
	(void)arr;
	(void)map;
	neighbors = NULL;
	node = neighbors;
	new_dscore = current->dist_score + 1;
	while (node != NULL)
	{
		temp = (t_astar *)node->content;
		next = node->next;
		if (new_dscore < temp->dist_score)
		{
			temp->prev = current;
			temp->dist_score = new_dscore;
			temp->heur_score = new_dscore + st_heuristic(vec(temp->pos.x, temp->pos.y), vec(end.x, end.y));
			ft_lstadd_front(open, node);
		}
		else
			free(node);
		node = next;
	}
}

t_astar *st_get_current(t_list *lst)
{
	t_astar	*temp;
	t_astar	*low;

	low = NULL;
	while (lst != NULL)
	{
		temp = (t_astar *)lst->content;
		if (low == NULL || low->heur_score > temp->heur_score)
			low = temp;
		lst = lst->next;
	}
	return (low);
}

// this could return after if statement is true as long as open 
// does not contain duplicates
void	st_mvnode(t_list **open, t_list **closed, t_astar *item)
{
	t_list	*node;
	t_list	*swap;

	node = *open;
	while (node != NULL && node->next != NULL)
	{
		if (node->next->content == item)
		{
			swap = node->next;
			node->next = swap->next;
			ft_lstadd_front(closed, swap);
			// return ;
		}
		else
			node = node->next;
	}
}

t_list	**astar(t_vect2 start, t_vect2 end, t_map *map)
{
	t_astar	*arr;
	t_astar	*current;
	t_list	*open;
	t_list	*closed;

	st_init_arr(map, &arr);
	arr[start.x + start.y * map->size.x].dist_score = 0;
	arr[start.x + start.y * map->size.x].heur_score = st_heuristic(vec(start.x, start.y), vec(end.x, end.y));
	closed = NULL;
	open = ft_lstnew(&arr[start.x + start.y * map->size.x]);
	if (open == NULL)
		exit_strerr(MALLOC_ERR);
	while (open != NULL)
	{
		current = st_get_current(open);
		if (current->pos.x == end.x && current->pos.y == end.y)
		{
			printf("yes!\n");
			return (NULL);
			// return (st_get_path(closed, current));
		}
		st_iter_neighbors(arr, current, &open, end, map);
		st_mvnode(&open, &closed, current);
	}
	st_freenodes(open);
	st_freenodes(closed);
	free(arr);
	return (NULL);
}
