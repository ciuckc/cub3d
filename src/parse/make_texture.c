/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 17:51:02 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/12 21:31:49 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_check_colour(char *path)
{
	uint32_t	i;
	uint32_t	clr_index;
	uint32_t	nr_len;

	nr_len = 0;
	i = 0;
	clr_index = 0;
	while (path[i] != '\0')
	{
		while (ft_isdigit(path[i]))
		{
			nr_len++;
			i++;
		}
		clr_index++;
		if (path[i] == '\0')
			continue ;
		else if (path[i] != ',' || nr_len > 3)
			exit_strerr(COL_ERR);
		nr_len = 0;
		i++;
	}
	if (clr_index != 3)
		exit_strerr(COL_ERR);
}

static uint32_t	st_get_clr(char *path)
{
	uint32_t	*channel;
	uint32_t	ch_i;
	uint32_t	i;

	i = 0;
	ch_i = 0;
	channel = (uint32_t [3]){0};
	while (true)
	{
		while (ft_isdigit(path[i]))
		{
			channel[ch_i] = channel[ch_i] * 10 + (path[i] - '0');
			i++;
		}
		if (path[i] == '\0')
			break ;
		ch_i++;
		i++;
	}
	return (get_rgba(channel[0], channel[1], channel[2], UINT8_MAX));
}

static void	st_check_path(char *path)
{
	uint32_t	len;
	int32_t		fd;

	len = ft_strlen(path);
	if (len <= 6)
		exit_strerr(EXT_ERR);
	if (ft_strncmp(path + (len - 6), ".xpm42", 6) != 0)
		exit_strerr(EXT_ERR);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_strerr(IMG_ERR);
	close(fd);
}

static mlx_image_t	*st_get_tex(char *path, mlx_t *mlx)
{
	xpm_t			*load_tex;
	mlx_texture_t	*tex;
	mlx_image_t		*image;

	load_tex = mlx_load_xpm42(path);
	if (load_tex == NULL)
		exit_strerr(LOAD_ERR);
	tex = ft_calloc(1, sizeof(mlx_texture_t));
	if (tex == NULL)
		exit_strerr(LOAD_ERR);
	*tex = load_tex->texture;
	image = mlx_texture_to_image(mlx, tex);
	if (image == NULL)
		exit_strerr(LOAD_ERR);
	free(tex);
	mlx_delete_xpm42(load_tex);
	return (image);
}

void	make_texture(char key, char *path, t_vars *vars)
{
	char	*table;
	t_tex	*texture;

	texture = vars->texture;
	table = (char [128]){['N'] = N, ['S'] = S, ['W'] = W, \
	['E'] = E, ['F'] = F, ['C'] = C};
	if (key == 'C' || key == 'F')
	{
		st_check_colour(path);
		texture[(int) table[(int) key]].is_clr = true;
		texture[(int) table[(int) key]].elem.clr = st_get_clr(path);
		return ;
	}
	st_check_path(path);
	texture[(int) table[(int) key]].is_clr = false;
	printf("loading texture from file...%s\n", path);
	texture[(int) table[(int) key]].elem.tex = st_get_tex(path, vars->mlx);
}
