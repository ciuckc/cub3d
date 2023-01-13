/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 21:50:29 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/13 20:27:06 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_check_map_content(char *str, uint32_t *i)
{
	char		*table;
	uint32_t	j;

	table = (char [128]){[' '] = true, ['0'] = true, ['1'] = true, ['\n'] = \
	true, ['N'] = true, ['S'] = true, ['W'] = true, ['E'] = true};
	while (str[*i] == '\n' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '\0')
		exit_strerr(NO_MAP_FOUND);
	j = *i;
	while (str[j] && table[(int) str[j]])
		j++;
	if (table[(int) str[j]] == false && str[j])
		exit_strerr(INV_MAP);
}

static void	st_check_pos(char *str, uint32_t i)
{
	char		*table;
	uint32_t	found;
	bool		player_found;

	found = 0;
	table = (char [128]){0};
	player_found = false;
	while (str[i])
	{
		table[(int) str[i]]++;
		player_found = ft_strchr("NSEW", str[i]);
		if (player_found)
			found++;
		if (table[(int) str[i]] > 1 && player_found)
			exit_strerr(POS_DUP_ERR);
		i++;
	}
	if (found != 1)
		exit_strerr(NO_PLR);
}

static void	st_check_nl(char *str, uint32_t i)
{
	uint32_t	line_len;

	line_len = 0;
	while (str[i])
	{
		while (str[i] != '\n' && str[i])
		{
			if (ft_isalnum(str[i]))
				line_len++;
			i++;
		}
		if (line_len == 0)
			exit_strerr(MAP_NL_ERR);
		line_len = 0;
		i++;
	}
}

static void	st_set_mapsize(t_map *map, char *map_str)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (map_str[i] != '\0')
	{
		if (map_str[i] == '\n')
			y++;
		i++;
	}
	x = (i - y) / y;
	map->size.x = x;
	map->size.y = y;
}

void	get_map(char *str, t_vars *vars, u_int32_t *i)
{
	int	j;

	j = 0;
	st_check_map_content(str, i);
	st_check_nl(str, *i);
	st_check_pos(str, *i);
	st_set_mapsize(&vars->map, str + *i);
	vars->map.grid = ft_calloc(vars->map.size.x * vars->map.size.y, \
	sizeof(char));
	while (str[*i])
	{
		if (str[*i] == '\n')
			(*i)++;
		if (str[*i] == '\0')
			break ;
		if (ft_isdigit(str[*i]))
			vars->map.grid[j] = str[*i] - '0';
		j++;
		(*i)++;
	}
	free(str);
}
