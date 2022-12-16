/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 15:49:16 by mbatstra      #+#    #+#                 */
/*   Updated: 2021/12/14 15:49:18 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (s == NULL)
		return (size);
	while (*s)
	{
		size++;
		s++;
	}
	return (size);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (!*s && !c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*dup;

	if (!s1)
		return (NULL);
	i = 0;
	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (dup);
	while (*s1 && n)
	{
		dup[i] = *s1;
		s1++;
		i++;
		n--;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(size * sizeof(char));
	if (!str)
		return (NULL);
	while (*s1)
	{
		str[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	set_tail(const char *buf, char *tail)
{
	char	*next;

	next = ft_strchr(buf, '\n');
	if (next)
		ft_strlcpy(tail, next + 1, ft_strlen(next));
	else
		tail[0] = '\0';
}
