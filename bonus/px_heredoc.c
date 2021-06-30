/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 22:35:36 by soooh             #+#    #+#             */
/*   Updated: 2021/07/01 04:35:29 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			clear_temp(void)
{
	char		**argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "-f";
	argv[1] = "./temp";
	argv[2] = NULL;
	if (fork() == 0)
		execve("/bin/rm", (char *const *)argv, NULL);
}

void			heredoc_cmd(char **argv)
{
	int			pipefd[2];
	pid_t		pid;
	t_ec		ec_cmd;
	int			status;

	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			px_error("pid error\n");
		redir_output(argv[5]);
		connect_pipe(pipefd, 0);
		execve_cmd(argv[4], &ec_cmd);
	}
	else if (pid == 0)
	{
		redir_input("./temp");
		connect_pipe(pipefd, 1);
		execve_cmd(argv[3], &ec_cmd);
	}
	else
		px_error("error");
}

int				heredoc(char **argv)
{
	int			fd;
	char		*buf;
	int			i;
	int			pipefd[2];

	i = 1;
	buf = 0;
	pipe(pipefd);
	fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		px_error("error_temp_file");
	write(STDOUT_FILENO, "heredoc> ", 9);
	while ((i = px_gnl(0, &buf)) > 0)
	{
		if (ft_strcmp(buf, argv[2]) == 0)
		{
			close(fd);
			return (0);
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}
	close(fd);
	return (0);
}
