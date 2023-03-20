/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 20:07:16 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/20 16:34:35 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	st_validate_map_name(char *map_name)
{
	u_int32_t	name_len;

	name_len = ft_strlen(map_name);
	if (name_len <= 4)
		return (false);
	if (ft_strncmp(map_name + (name_len - 4), ".cub", 4) != 0)
		return (false);
	return (true);
}

static bool	st_make_map_str(char **str_map, int32_t fd)
{
	char	*line;
	char	*temp;

	*str_map = NULL;
	temp = ft_strdup("");
	if (temp == NULL)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			if (*str_map == NULL)
				return (false);
			return (true);
		}
		*str_map = ft_strjoin(temp, line);
		if (*str_map == NULL)
			return (false);
		free(temp);
		free(line);
		temp = *str_map;
	}
}

static void	st_trim_str(char **str)
{
	char	*trim_str;

	trim_str = ft_strtrim(*str, "\n");
	if (trim_str == NULL)
		exit_strerr(MALLOC_ERR);
	free(*str);
	*str = trim_str;
}

void	parse(int argc, char **argv, t_vars *vars)
{
	char		*str_map;
	uint32_t	str_index;
	int32_t		fd;

	if (argc != 2)
		exit_strerr(ARG_ERR);
	if (!st_validate_map_name(*(argv + 1)))
		exit_strerr(MAP_NAME_ERR);
	fd = open(*(argv + 1), O_RDONLY);
	if (fd == -1)
		exit_strerr(FD_ERR);
	if (!st_make_map_str(&str_map, fd))
		exit_strerr(MALLOC_ERR);
	st_trim_str(&str_map);
	str_index = 0;
	get_textures(str_map, vars, &str_index);
	get_map(str_map, vars, &str_index);
	free(str_map);
}
