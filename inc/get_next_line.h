/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 15:49:07 by mbatstra      #+#    #+#                 */
/*   Updated: 2023/01/09 20:53:37 by scristia      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	gnl_strlcpy(char *dst, const char *src, size_t n);
size_t	gnl_strlen(const char *s);
char	*append(char *line, const char *buf, char *next);
char	*gnl_strjoin(const char *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strndup(const char *s1, size_t n);
char	*get_next_line(int fd);
void	set_tail(const char *buf, char *tail);
int		read_line(char **line, char *buf, int fd);

#endif
