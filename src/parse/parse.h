/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:02:30 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/10 18:08:28 by scristia      ########   odam.nl         */
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

/**
 * @brief Print error and str_err and exit with code 1
 * 
 * @param str_err the reason of exiting.
 */
void	exit_strerr(char *str_err);

#endif