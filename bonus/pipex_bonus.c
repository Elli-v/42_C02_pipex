/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/26 02:49:48 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			px_error(char *str)
{
	perror(str);
	exit(1);
}

static void		clear_temp(void)
{
	char **argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "-f";
	argv[1] = "./temp";
	argv[2] = NULL;
	if (fork() == 0)
		execve("/bin/rm", (char *const *)argv, NULL);
}

void			heredoc(t_px *px_cmd)
{
	int			fd;
	char		*buf;
	int			i;

	i = 1;
	buf = 0;
	fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		px_error("임시 파일에 문제 생김;;");
	write(STDOUT_FILENO, "heredoc> ", 9);
	while ((i = get_next_line(0, &buf)) > 0)
	{
		if (ft_strcmp(buf, px_cmd->infile) == 0)
			break;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}
	close(fd);
	redir_input("./temp");
	clear_temp();
}

int				main(int argc, char **argv)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];

	if (argc == 0)
		px_error("인자 갯수 안 맞음");
	init_px_cmd(argv, &px_cmd);
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		redir_output(px_cmd.outfile);
		connect_pipe(pipefd, 0);
		execve_cmd(px_cmd.cmd2, &ec_cmd);
	}
	else if (pid == 0)
	{
		if (ft_strcmp(argv[1], "heredoc") == 0)
			heredoc(&px_cmd);
		connect_pipe(pipefd, 1);
		execve_cmd(px_cmd.cmd1, &ec_cmd);
	}
	return (0);
}
