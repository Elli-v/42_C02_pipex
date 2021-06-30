/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:23 by soooh             #+#    #+#             */
/*   Updated: 2021/07/01 04:00:25 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

#  define BUFFER_SIZE 5000
#  define OPEN_MAX 32

typedef struct	s_execve {
	const char	*cmd[5];
	char *const	*argv;
	char *const	*envp;
}				t_ec;

typedef struct	s_pipex {
	char		*infile;
	char		*outfile;
	char		**cmd;
	int			pipe_cnt;
	int			prev_pipefd[2];
	int			pipefd[2];
}				t_px;

typedef struct	s_fd {
	int			prev_pipefd[2];
	int			pipefd[2];
}				t_fd;


/*
** gnl
*/
int				px_gnl(int fd, char **line);

/*
** px_heredoc.c
*/
void			clear_temp(void);
void			heredoc_cmd(char **argv);
int				heredoc(char **argv);

/*
** px_multi_pipe.c
*/
int				multi_pipe(int argc, char **argv, t_px *px_cmd);
void			recursive_pipe(char **argv, t_px *px_cmd, int i);

/*
** px_utils_bonus2.c
*/
int				ft_strcmp(const char *s1, const char *s2);

/*
** px_utils.c
*/
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dest, char *src, size_t size);
char			*ft_strdup(const char *src);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			*ft_strjoin(char *s1, char *s2);

/*
** ft_split.c
*/
void			*ft_calloc(size_t count, size_t size);
char			**ft_split(char const *s, char c);

/*
** px_redirection.c
*/
void			redir_input(char *file);
void			redir_output(char *file);

/*
** px_pipe.c
*/
void			init_px_cmd(int argc, char **argv, t_px *px_cmd);
void			connect_pipe(int pipefd[2], int num);
void			close_pipe(int pipefd[2]);
void			b_connect_pipe(int pipefd[2], int num);

/*
** px_execve.c
*/
void			init_ec_cmd(const char *cmd, t_ec *ec_cmd);
void			execve_cmd(const char *path, t_ec *ec_cmd);

/*
** pipex.c
*/
void			px_error(char *str);
int				main(int argc, char **argv);

#endif
