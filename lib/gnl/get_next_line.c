/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 15:45:32 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/09 20:55:03 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append(char *line, const char *buf, char *next)
{
	char	*str;
	char	*temp;
	int		len;

	if (next)
		len = next - buf + 1;
	else
		len = BUFFER_SIZE + 1;
	temp = gnl_strndup(buf, len);
	if (!temp)
		return (NULL);
	str = gnl_strjoin(line, temp);
	free(temp);
	return (str);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	index;

	index = 0;
	src_len = gnl_strlen(src);
	if (!dstsize)
		return (src_len);
	while (index < (dstsize - 1) && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (src_len);
}

int	read_line(char **line, char *tail, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*next;
	char	*temp;
	int		num_bytes;

	next = NULL;
	num_bytes = BUFFER_SIZE;
	while (num_bytes == BUFFER_SIZE && !next)
	{
		num_bytes = read(fd, buf, BUFFER_SIZE);
		buf[num_bytes] = '\0';
		next = gnl_strchr(buf, '\n');
		temp = append(*line, buf, next);
		free(*line);
		*line = gnl_strndup(temp, gnl_strlen(temp));
		if (!*line || !temp)
		{
			free(*line);
			free(temp);
			return (0);
		}
		free(temp);
	}
	set_tail(buf, tail);
	return (num_bytes);
}

char	*get_next_line(int fd)
{
	static char	tail[BUFFER_SIZE + 1];
	char		*line;
	char		*next;
	int			num_bytes;

	next = gnl_strchr(tail, '\n');
	if (next)
	{
		line = gnl_strndup(tail, next - tail + 1);
		gnl_strlcpy(tail, next + 1, gnl_strlen(next));
		return (line);
	}
	line = gnl_strndup(tail, gnl_strlen(tail));
	if (!line)
		return (NULL);
	num_bytes = read_line(&line, tail, fd);
	if (num_bytes == -1 || !gnl_strlen(line))
	{
		free(line);
		return (NULL);
	}
	return (line);
}
