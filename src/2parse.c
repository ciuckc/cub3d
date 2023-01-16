/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:43:07 by mbatstra          #+#    #+#             */
/*   Updated: 2022/12/08 18:01:10 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"

static void	st_str_append(char **map, const char *ln)
{
	char	*temp;

	temp = ft_strndup(*map, ft_strlen(*map));
	free(*map);
	if (temp == NULL)
		exit(EXIT_FAILURE);
	*map = ft_strjoin(temp, ln);
	free(temp);
	if (*map == NULL)
		exit(EXIT_FAILURE);
}

// read file into a single string
// set size.y for later use
static char	*st_fil2str(int fd, t_map *map)
{
	char	*c_map;
	char	*ln;

	c_map = ft_strdup("");
	ln = get_next_line(fd);
	map->size.y = -1;
	while (ln != NULL)
	{
		map->size.y++;
		st_str_append(&c_map, ln);
		free(ln);
		ln = get_next_line(fd);
	}
	free(ln);
	if (ft_strlen(c_map) == 0)
	{
		free(c_map);
		printf("Error\nInvalid map\n");
		exit(EXIT_FAILURE);
	}
	return (c_map);
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

static void	st_load_map(t_map *map, char *map_str)
{
	int	i_old;
	int	i_new;

	i_old = 0;
	i_new = 0;
	while (map_str[i_old] != '\0')
	{
		if (map_str[i_old] == '0')
			map->grid[i_new] = FLOOR;
		else if (map_str[i_old] == '1')
			map->grid[i_new] = WALL;
		else if (ft_strchr("NSEW", map_str[i_old]))
			map->grid[i_new] = START_POS;
		if (map_str[i_old] != '\n')
			i_new++;
		i_old++;
	}
}

void	parse(char **argv, t_map *map)
{
	char	*map_str;
	char	*ext;
	int		fd;

	ext = ft_strchr(argv[1], '.'); // alternatiely do strlen - 4
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || ft_strncmp(ext, ".cub", ft_strlen(ext)))
	{
		if (fd > 0)
			close(fd);
		printf("Error\nUnable to open map file\n");
		exit(EXIT_FAILURE);
	}
	map_str = st_fil2str(fd, map);
	close(fd);
	st_set_mapsize(map, map_str);
	map->grid = (int *)malloc(sizeof(int) * map->size.x * map->size.y);
	if (map->grid == NULL)
	{
		printf("Error\n");
		free(map_str);
		exit(EXIT_FAILURE);
	}
	st_load_map(map, map_str);
	free(map_str);
}
