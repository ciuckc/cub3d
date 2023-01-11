/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_index_first_line.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 20:23:35 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/10 21:58:43 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int32_t	st_len_to_char(char *str, char c)
{
	int32_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static bool	st_line_is_valid(char *table)
{
	int32_t	i;

	i = 0;
	while (i < 128)
	{
		if (table[i] && !ft_strchr(MAP_CONTENT, i))
			return (false);
		i++;
	}
	return (true);
}

static bool	st_is_first_map_line(char *str_map, int32_t i)
{
	char	*table;

	table = (char [128]){0};
	if (str_map[i] == '\n')
		return (false);
	while (str_map[i] != '\n' && str_map[i] != '\0')
	{
		table[(int32_t)str_map[i]]++;
		i++;
	}
	if (st_line_is_valid(table))
		return (true);
	return (false);
}

int32_t	get_index_first_line(char *str_map)
{
	int32_t	i;

	i = 0;
	while (str_map[i])
	{
		if (st_is_first_map_line(str_map, i))
			return (i);
		i += st_len_to_char(str_map + i, '\n');
		if (str_map[i] == '\0')
			break ;
		else
			i++;
	}
	return (-1);
}
