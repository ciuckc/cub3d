/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 15:49:07 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/12/08 16:36:21 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);
char	*append(char *line, const char *buf, char *next);
char	*ft_strjoin(const char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s1, size_t n);
char	*get_next_line(int fd);
void	set_tail(const char *buf, char *tail);
int		read_line(char **line, char *buf, int fd);

#endif
