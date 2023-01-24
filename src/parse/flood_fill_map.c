/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:34:25 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/24 16:07:44 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

static void	st_free_tiles(t_tile **tile_map, int32_t len)
{
	int32_t	i;

	i = 0;
	while (i < len)
	{
		free(tile_map[i]);
		i++;
	}
	free(tile_map);
}

void	flood_fill_map(t_vars *vars)
{
	t_tile	**flood_map;
	int32_t	tiles_y_size;

	tiles_y_size = vars->map.size.y;
	flood_map = init_tile_map(vars->map.size.x, tiles_y_size);
	st_init_each_tile(vars->map, flood_map);
	st_fill_from_player(vars, flood_map);
	crop_map(&vars->map, flood_map, &vars->player);
	st_free_tiles(flood_map, tiles_y_size);
}
