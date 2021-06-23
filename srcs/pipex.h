/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:23 by soooh             #+#    #+#             */
/*   Updated: 2021/06/24 02:16:42 by soooh            ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size);
int		w_cnt(const char *str, char c);
int		ft_word_len(const char *word, char c);
int		ft_add(const char *str, char c, char *res);
void	ft_increment(char letter, int *i);
char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);
size_t		ft_strlcat(char *dest, char *src, size_t size);
char		*ft_strdup(const char *src);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strjoin(char *s1, char *s2);
void	px_error(char *str);


int				main(int argc, char **argv);

#endif