/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 21:50:29 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/12 22:22:46 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	st_check_map_content(char *str, uint32_t *i)
{
	char		*table;
	uint32_t	j;

	table = (char [128]){[' '] = true, ['0'] = true, ['1'] = true, ['\n'] = \
	true};
	while (str[*i] == '\n' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '\0')
		exit_strerr(NO_MAP_FOUND);
	j = *i;
	while (str[j])
	{
		if (table[(int) str[j]] == false)
			exit_strerr(INV_MAP);
		j++;
	}
}

void	get_map(char *str, t_vars *vars, u_int32_t *i)
{
	(void)vars;
	st_check_map_content(str, i);
}
