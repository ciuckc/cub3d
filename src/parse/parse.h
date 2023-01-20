/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:02:30 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/20 03:51:52 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "libft.h"
# include "math.h"
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
# define INV_MAP "Please provide a map with valid content!\n"
# define DUP_TEX "Found texture duplicate!\n"
# define ELEM_ERR "Invalid texture elements!\n"
# define EXT_ERR "Invalid texture. Needs to end in \".xpm42\"\n"
# define COL_ERR "Invalid colour. Needs to have (R,G,B) values.\n"
# define IMG_ERR "Error while opening the textures. Make sure it exists or \
you have the right permissions!\n"
# define LOAD_ERR "Could not load the texture!\n"
# define MAP_NL_ERR "Consecutive new-lines inside the map!\n"
# define POS_DUP_ERR "Player position duplicate found!\n"
# define NO_PLR "Could not resolve player position.\n"
# define INV_WALL_ERR "Map has openings in the walls.\n"

typedef enum e_front_neighbour
{
	UP = 1,
	RIGHT = 2,
	DOWN = 4,
	LEFT = 8
}		t_neighbour;

typedef struct s_tile
{
	uint16_t	type;
	uint16_t	frontier_neighbour;
	bool		reached;
}		t_tile;

/**
 * @brief Print error and str_err and exit with code 1
 * 
 * @param str_err the reason of exiting.
 */
void	exit_strerr(char *str_err);

void	get_textures(char *str, t_vars *vars, uint32_t *i);

void	get_map(char *str, t_vars *vars, uint32_t *i);

void	make_texture(char key, char *path, t_vars *vars);

void	set_map_content(t_vars *vars, char *str);

void	flood_fill_map(t_vars *vars);

void	fill_from_pos(t_tile **map, t_list *queue, t_vect2 m_size);

void	reach_neighbours(t_tile **map, t_list *queue);

void	add_neighbours_to_queue(t_tile **map, t_list *queue);

t_vect2	*find_unreached_spots(t_tile **map, t_vect2 m_size);

#endif