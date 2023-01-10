/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:02:30 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/10 20:25:16 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

// Error message for problems during parsing
# define ARG_ERR "Usage: ./cub3d [.cub map]\n"
# define MAP_NAME_ERR "Please provide a valid \".cub\" map.\n"
# define FD_ERR "Error while opening the map or the name doesn't exist.\n"
# define MALLOC_ERR "Error while allocating!\n"
# define NO_MAP_FOUND "Please provide a map with valid contents.\n"

/*
Chars which are valid map content -> SUPER IMPORTANT FOR LATER IF WE ADD
MORE SPRITES OR OTHER STUFF.
*/
# define MAP_CONTENT " 01"

/**
 * @brief Print error and str_err and exit with code 1
 * 
 * @param str_err the reason of exiting.
 */
void	exit_strerr(char *str_err);

void	store_map_and_textures(char *str_map, t_vars *vars);

int32_t	get_index_first_line(char *str_map);

#endif