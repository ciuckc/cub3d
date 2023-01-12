/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_map_and_textures.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 19:10:00 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/12 22:21:52 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	store_map_and_textures(char *str_map, t_vars *vars)
{
	uint32_t	str_index;

	str_index = 0;
	get_textures(str_map, vars, &str_index);
	get_map(str_map, vars, &str_index);
	exit_strerr("OK");
}

//	get_map
//	- find first line of the map
//	- check from there until the end of the string if the only content is
// only the contents of MAP_CONTENT, if not screw out of the program
//	- get size of it and allocate, store the size in vars->map->size
//	- store the content in the vars->map->grid