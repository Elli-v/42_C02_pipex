/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:23 by soooh             #+#    #+#             */
/*   Updated: 2021/06/24 18:22:02 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_execve {
	const char	*cmd[5];
	char *const	*argv;
	char *const	*envp;
}				t_ec;

typedef struct	s_pipex {
	char		*infile;
	char		*outfile;
	char		*cmd1;
	char		*cmd2;
}				t_px;

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
void			init_px_cmd(char **argv, t_px *px_cmd);
void			connect_pipe(int pipefd[2], int num);

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
