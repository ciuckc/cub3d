/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_map_and_textures.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 19:10:00 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/13 20:18:04 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_get_player_pos(t_vars *var)
{
	t_fvect2	*table;
	uint32_t	player_idx;
	uint32_t	len;

	table = (t_fvect2 [128]){['N'] = {0.0, -1.0}, ['S'] = {0.0, 1.0}, \
	['W'] = {-1.0, 0.0}, ['E'] = {1.0, 0.0}};
	len = var->map.size.x * var->map.size.y;
	player_idx = 0;
	while (player_idx < len)
	{
		if (ft_strchr("NSWE", var->map.grid[player_idx]))
			break ;
		player_idx++;
	}
	var->player.pos.y = (player_idx / var->map.size.x) + 0.5;
	var->player.pos.x = (player_idx % var->map.size.x) + 0.5;
	var->player.dir = table[player_idx];
	var->map.grid[player_idx] = START_POS;
}

void	store_map_and_textures(char *str_map, t_vars *vars)
{
	uint32_t	str_index;

	str_index = 0;
	get_textures(str_map, vars, &str_index);
	get_map(str_map, vars, &str_index);
	st_get_player_pos(vars);
}

//	get_map
//	- find first line of the map
//	- check from there until the end of the string if the only content is
// only the contents of MAP_CONTENT, if not screw out of the program
//	- get size of it and allocate, store the size in vars->map->size
//	- store the content in the vars->map->grid