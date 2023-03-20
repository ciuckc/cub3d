/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 17:51:02 by scristia      #+#    #+#                 */
/*   Updated: 2023/03/20 16:55:40 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	st_check_colour(char *path)
{
	uint32_t	clr_index;
	uint32_t	nr_len;

	nr_len = 0;
	clr_index = 0;
	while (*path != '\0')
	{
		while (*path == ' ')
			path++;
		while (ft_isdigit(*path))
		{
			nr_len++;
			path++;
		}
		while (*path == ' ')
			path++;
		clr_index++;
		if (*path == '\0')
			continue ;
		else if (*path != ',' || nr_len > 3)
			return (false);
		nr_len = 0;
		path++;
	}
	return (clr_index == 3);
}

static uint32_t	st_get_clr(char *path)
{
	uint32_t	*channel;
	uint32_t	ch_i;

	if (!ft_strncmp(path, "default", 8))
		return (0);
	ch_i = 0;
	channel = (uint32_t [3]){0};
	while (true)
	{
		while (*path == ' ')
			path++;
		while (ft_isdigit(*path))
		{
			channel[ch_i] = channel[ch_i] * 10 + (*path - '0');
			path++;
		}
		while (*path == ' ')
			path++;
		if (*path == '\0')
			break ;
		ch_i++;
		path++;
	}
	return (get_rgba(channel[0], channel[1], channel[2], 255));
}

static bool	st_check_path(char *path)
{
	uint32_t	len;
	int32_t		fd;

	len = ft_strlen(path);
	if (len <= 6)
		return (false);
	if (ft_strncmp(path + (len - 6), ".xpm42", 6) != 0)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static mlx_image_t	*st_get_tex(char *path, mlx_t *mlx)
{
	xpm_t			*load_tex;
	mlx_texture_t	tex;
	mlx_image_t		*image;

	load_tex = mlx_load_xpm42(path);
	if (load_tex == NULL)
		exit_strerr(LOAD_ERR);
	tex = load_tex->texture;
	image = mlx_texture_to_image(mlx, &tex);
	if (image == NULL)
		exit_strerr(LOAD_ERR);
	mlx_delete_xpm42(load_tex);
	return (image);
}

void	make_texture(char key, char *path, t_vars *vars)
{
	char	*table;

	table = (char [128]){['N'] = N, ['S'] = S, ['W'] = W, \
	['E'] = E, ['F'] = F, ['C'] = C};
	if (key == 'C' || key == 'F')
	{
		if (st_check_colour(path) || (!ft_strncmp(path, "default", 8) && \
			key == 'C'))
		{
			if (key == 'C')
				vars->ceil_clr = st_get_clr(path);
			else
				vars->floor_clr = st_get_clr(path);
		}
		else if (st_check_path(path) && key != 'C')
			vars->texture[(int) table[(int) key]] = st_get_tex(path, vars->mlx);
		else
			exit_strerr("Invalid floor or ceiling colour/texture.\n");
	}
	else
	{
		st_check_path(path);
		vars->texture[(int) table[(int) key]] = st_get_tex(path, vars->mlx);
	}
}
