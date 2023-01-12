/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_map_and_textures.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 19:10:00 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/12 20:45:31 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_get_map(char *str_map, t_map *map)
{
	int32_t	first_map_line_index;

	(void)map;
	first_map_line_index = get_index_first_line(str_map);
	if (first_map_line_index == -1)
		exit_strerr(NO_MAP_FOUND);
	printf("%d\n", first_map_line_index);
}

void	store_map_and_textures(char *str_map, t_vars *vars)
{
	uint32_t	str_index;

	str_index = 0;
	get_textures(str_map, vars, &str_index);
	st_get_map(str_map, &vars->map);
}

//	get_map
//	- find first line of the map
//	- check from there until the end of the string if the only content is
// only the contents of MAP_CONTENT, if not screw out of the program
//	- get size of it and allocate, store the size in vars->map->size
//	- store the content in the vars->map->grid