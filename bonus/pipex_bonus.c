/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/25 01:58:42 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			px_error(char *str)
{
	perror(str);
	exit(1);
}

int				main(int argc, char **argv)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];

	if (argc != 5)
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
		redir_input(px_cmd.infile);
		connect_pipe(pipefd, 1);
		execve_cmd(px_cmd.cmd1, &ec_cmd);
	}
	return (0);
}
