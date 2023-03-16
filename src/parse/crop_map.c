/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   crop_map.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/23 17:07:40 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/16 13:23:41 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_copy_content(t_map *unsan_map, uint8_t *san_map, t_vect2 \
*ranges)
{
	int32_t	y;
	int32_t	x;

	y = ranges[FIRST].y - 1;
	x = ranges[FIRST].x - 1;
	while (y < ranges[LAST].y + 2)
	{
		x = ranges[FIRST].x - 1;
		while (x < ranges[LAST].x + 2)
		{
			*san_map = mapindex(unsan_map, x, y);
			san_map++;
			x++;
		}
		y++;
	}
}

static void	st_replace_unreached(t_tile **tiles, uint8_t *san_map, t_vect2 \
*ranges)
{
	int32_t	y;
	int32_t	x;

	y = ranges[FIRST].y - 1;
	x = ranges[FIRST].x - 1;
	while (y < ranges[LAST].y + 2)
	{
		x = ranges[FIRST].x - 1;
		while (x < ranges[LAST].x + 2)
		{
			if (!tiles[y][x].reached || tiles[y][x].type == UNREACH)
				*san_map = WALL;
			x++;
			san_map++;
		}
		y++;
	}
}

static void	st_get_new_player_pos(t_map *unsan_map, t_player *plr)
{
	uint32_t	player_idx;
	uint32_t	len;

	len = unsan_map->size.x * unsan_map->size.y;
	player_idx = 0;
	while (unsan_map->grid[player_idx] != START_POS)
		player_idx++;
	plr->pos.x = (player_idx % unsan_map->size.x) + 0.5;
	plr->pos.y = (player_idx / unsan_map->size.x) + 0.5;
}

void	crop_map(t_map *unsan_map, t_tile **tiles, t_player *plr)
{
	t_vect2	ranges[2];
	uint8_t	*san_map;
	int32_t	new_x;
	int32_t	new_y;

	get_map_range(unsan_map, tiles, ranges);
	new_x = ranges[LAST].x - ranges[FIRST].x + 3;
	new_y = ranges[LAST].y - ranges[FIRST].y + 3;
	san_map = ft_calloc(new_x * new_y, sizeof(uint8_t));
	if (san_map == NULL)
		exit_strerr(MALLOC_ERR);
	st_copy_content(unsan_map, san_map, ranges);
	st_replace_unreached(tiles, san_map, ranges);
	free(unsan_map->grid);
	unsan_map->grid = san_map;
	unsan_map->size = (t_vect2){new_x, new_y};
	st_get_new_player_pos(unsan_map, plr);
	printf("new px: %f new py: %f\n", plr->pos.x, plr->pos.y);
}
