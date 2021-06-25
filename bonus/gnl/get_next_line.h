/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:03:34 by daelee            #+#    #+#             */
/*   Updated: 2021/06/26 02:53:15 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 32
# endif

int			get_next_line(int fd, char **line);

size_t		gnl_strlen(const char *str);
size_t		gnl_strlcpy(char *dest, const char *src, size_t size);
size_t		gnl_strlcat(char *dest, const char *src, size_t size);
char		*gnl_strdup(const char *src);
char		*gnl_strjoin(char *s1, char *s2);

#endif
