/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:34:25 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/20 03:41:43 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_tile	**st_init_map(t_map grid)
{
	t_tile	**tiles;
	int32_t	i;

	tiles = ft_calloc(grid.size.y, sizeof(t_tile *));
	if (tiles == NULL)
		exit_strerr(MALLOC_ERR);
	i = 0;
	while (i < grid.size.y)
	{
		tiles[i] = ft_calloc(grid.size.x, sizeof(t_tile));
		if (tiles[i] == NULL)
			exit_strerr(MALLOC_ERR);
		i++;
	}
	return (tiles);
}

static void	st_init_each_tile(t_map grid, t_tile **tile)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	while (y < grid.size.y)
	{
		x = 0;
		while (x < grid.size.x)
		{
			tile[y][x].type = mapindex(&grid, x, y);
			tile[y][x].reached = false;
			if (tile[y][x].type == WALL || tile[y][x].type == START_POS)
				tile[y][x].reached = true;
			x++;
		}
		y++;
	}
}

static void	st_fill_from_player(t_vars *vars, t_tile **tile_map)
{
	t_list	*queue;
	t_vect2	*player_pos;

	player_pos = ft_calloc(1, sizeof(t_vect2));
	if (player_pos == NULL)
		exit_strerr(MALLOC_ERR);
	*player_pos = (t_vect2){.x = (int)vars->player.pos.x, \
	.y = (int)(vars->player.pos.y)};
	queue = ft_lstnew(player_pos);
	if (queue == NULL)
		exit_strerr(MALLOC_ERR);
	fill_from_pos(tile_map, queue, vars->map.size);
}

static void	st_fill_left_spots(t_vars *vars, t_tile **tile_map)
{
	t_vect2	*left_spot;
	t_list	*queue;

	while (true)
	{
		left_spot = find_unreached_spots(tile_map, vars->map.size);
		if (left_spot == NULL)
			return ;
		queue = ft_lstnew(left_spot);
		if (queue == NULL)
			exit_strerr(MALLOC_ERR);
		fill_from_pos(tile_map, queue, vars->map.size);
	}
}

void	flood_fill_map(t_vars *vars)
{
	t_tile	**flood_map;

	flood_map = st_init_map(vars->map);
	st_init_each_tile(vars->map, flood_map);
	st_fill_from_player(vars, flood_map);
	st_fill_left_spots(vars, flood_map);
}
