/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:23 by soooh             #+#    #+#             */
/*   Updated: 2021/06/22 22:37:19 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h> //wait, waitpid 함수 사용시 필요한 헤더
# include <stdio.h> // 지우자 지우자 ~

typedef struct	    s_execve {
	const char      *cmd[5];
	char *const	    *argv;
	char *const	    *envp;
}				    t_ec;

typedef struct	    s_pipex {
	char		    *infile;
	char		    *outfile;
	char		    *cmd1;
	char		    *cmd2;
}				    t_px;

void		*ft_calloc(size_t n, size_t size);
void	ft_bzero(void *s, size_t n);
// static int		ft_wcount(char const *s, char c);
// static char		*ft_wlen(int *a, const char *s, char c);
char			**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strjoin(char *s1, char *s2);

#endif