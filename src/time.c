/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:57:21 by mbatstra          #+#    #+#             */
/*   Updated: 2023/02/20 17:47:10 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long long	time_gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long long	time_tdelta(long long tzero)
{
	return (time_gettime() - tzero);
}
