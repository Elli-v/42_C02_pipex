/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:23 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 19:54:41 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE 5000
# define OPEN_MAX 32

typedef struct s_execve {
	const char	*cmd[5];
	char		*file;
	char *const	*argv;
	char *const	*envp;
	char		**envp_list;
	char		**temp;
}				t_ec;

typedef struct s_pipex {
	char		*infile;
	char		*outfile;
	char		**cmd;
	int			pipe_cnt;
	int			prev_pipefd[2];
	int			pipefd[2];
	char		**temp;
}				t_px;

/*
** px_gnl.c
*/
int				find_n(char *backup);
int				div_line(char **backup, char **line, int idx_num);
int				onandon(char **backup, char **line, int save_str);
int				px_gnl(int fd, char **line);

/*
** px_heredoc.c
*/
void			clear_temp(void);
void			heredoc_cmd(char **argv, char **envp);
int				heredoc(char **argv);

/*
** px_multi_pipe.c
*/
void			hand_over(t_px *px_cmd);
void			last_cmd(t_px *px_cmd, t_ec *ec_cmd, int i);
int				multi_pipe(int argc, char **argv, char **envp, t_px *px_cmd);
void			recursive_pipe(char **argv, t_px *px_cmd, int i);

/*
** px_utils_bonus.c
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
** px_redirection_bonus.c
*/
void			redir_input(char *file);
void			redir_output(char *file);

/*
** px_pipe_bonus.c
*/
void			init_px_cmd(int argc, char **argv, t_px *px_cmd);
void			connect_pipe(int pipefd[2], int num);
void			close_pipe(int pipefd[2]);
void			b_connect_pipe(int pipefd[2], int num);

/*
** px_execve_bonus.c
*/
char			*ft_strstr(char *str, char *to_find);
void			init_envp(t_ec *ec_cmd);
void			init_ec_cmd(const char *cmd, t_ec *ec_cmd);
void			execve_cmd(const char *path, t_ec *ec_cmd);

/*
** pipex_bonus.c
*/
void			px_error(char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				main(int argc, char **argv, char **envp);

#endif
