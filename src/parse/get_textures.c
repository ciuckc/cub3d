/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 17:35:39 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/25 17:54:04 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static bool	st_found_textures(char *table)
{
	char		*textures;
	uint32_t	found;
	uint32_t	i;

	textures = TEXTURES;
	found = 0;
	i = 0;
	while (textures[i])
	{
		if (table[(int) textures[i]])
			found++;
		i++;
	}
	return (found == sizeof(TEXTURES) - 1);
}

static bool	st_is_valid_element(char *str, uint32_t *i)
{
	char	**keys;

	keys = (char *[]){"NO ", "SO ", "EA ", "WE ", "F ", "C ", NULL};
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	if (str[*i] == '\n' || str[*i] == '\0')
		return (false);
	while (*keys)
	{
		if (!ft_strncmp(str + *i, *keys, ft_strlen(*keys)))
			return (true);
		keys++;
	}
	return (false);
}

static char	st_get_key(char *str, uint32_t *i, char *table)
{
	char	found;

	found = str[*i];
	if (table[(int) found])
		exit_strerr(DUP_TEX);
	table[(int) found]++;
	while (ft_isalpha(str[*i]) && str[*i])
		(*i)++;
	if (str[*i] == '\0')
		exit_strerr(ELEM_ERR);
	while (str[*i] == ' ')
		(*i)++;
	if (ft_iswspace(str[*i]))
		exit_strerr(ELEM_ERR);
	return (found);
}

static char	*st_get_path(char *str, uint32_t *i)
{
	uint32_t	len;
	char		*un_trim;
	char		*path;

	len = 0;
	while ((str + *i)[len] != '\n' && (str + *i)[len] != '\0')
		len++;
	if ((str + *i)[len] == '\0')
		exit_strerr(EXT_ERR);
	un_trim = ft_substr(str, *i, len);
	if (un_trim == NULL)
		exit_strerr(MALLOC_ERR);
	path = ft_strtrim(un_trim, " ");
	if (path == NULL)
		exit_strerr(MALLOC_ERR);
	while (str[*i] != '\n')
		(*i)++;
	free(un_trim);
	return (path);
}

void	get_textures(char *str, t_vars *vars, uint32_t *i)
{
	char		*table;
	char		*path;
	char		key;

	table = (char [128]){0};
	while (!st_found_textures(table))
	{
		while (str[*i] == '\n' && str[*i])
			(*i)++;
		if (str[*i] == '\0')
			exit_strerr(NO_MAP_FOUND);
		if (!st_is_valid_element(str, i))
			exit_strerr(ELEM_ERR);
		key = st_get_key(str, i, table);
		path = st_get_path(str, i);
		make_texture(key, path, vars);
	}
}
