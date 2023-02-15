/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 19:28:06 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/02/13 15:28:48 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint8_t	get_red(uint32_t clr)
{
	return (clr >> 24 & 0xff);
}

uint8_t	get_grn(uint32_t clr)
{
	return (clr >> 16 & 0xff);
}

uint8_t	get_blu(uint32_t clr)
{
	return (clr >> 8 & 0xff);
}

uint8_t	get_alpha(uint32_t clr)
{
	return (clr & 0xff);
}
