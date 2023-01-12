/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:02:30 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/12 20:42:02 by scristia      ########   odam.nl         */
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
# define DUP_TEX "Found texture duplicate!\n"
# define ELEM_ERR "Invalid texture elements!\n"
# define EXT_ERR "Invalid texture. Needs to end in \".xpm42\"\n"
# define COL_ERR "Invalid colour. Needs to have (R,G,B) values.\n"
# define IMG_ERR "Error while opening the textures. Make sure it exists or \
you have the right permissions!\n"
# define LOAD_ERR "Could not load the texture!"

/**
 * @brief Print error and str_err and exit with code 1
 * 
 * @param str_err the reason of exiting.
 */
void	exit_strerr(char *str_err);

void	store_map_and_textures(char *str_map, t_vars *vars);

void	get_textures(char *str, t_vars *vars, uint32_t *i);

void	make_texture(char key, char *path, t_vars *vars);

int32_t	get_index_first_line(char *str_map);

#endif