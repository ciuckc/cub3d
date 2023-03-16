/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_strerr.c                                      :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: scristia <scristia@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 21:39:25 by scristia      #+#    #+#                 */
/*   Updated: 2023/01/10 15:58:28 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	exit_strerr(char *str_err)
{
	dprintf(2, "Error!\n");
	dprintf(2, "%s", str_err);
	exit(EXIT_FAILURE);
}
