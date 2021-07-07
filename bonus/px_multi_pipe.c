/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_multi_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 03:59:27 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 20:06:42 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			last_cmd(t_px *px_cmd, t_ec *ec_cmd, int i)
{
	redir_output(px_cmd->outfile);
	b_connect_pipe(px_cmd->pipefd, 0);
	printf(">>>>>s = %s\n", px_cmd->cmd[i]);
	execve_cmd(px_cmd->cmd[i], ec_cmd);
}


int				multi_pipe(int argc, char **argv, char **envp, t_px *px_cmd)
{
	pid_t		pid;
	int			status;
	t_ec		ec_cmd;
	int			i;

	i = 0;
	ec_cmd.temp = envp;
	printf("2\n");
	init_px_cmd(argc, argv, px_cmd);
	pipe(px_cmd->pipefd);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			px_error("pid error\n");
		close_pipe(px_cmd->prev_pipefd);
		recursive_pipe(argv, px_cmd, i);
	}
	else if (pid == 0)
	{
		printf("3\n");
		redir_input(px_cmd->infile);
		printf("4\n");
		b_connect_pipe(px_cmd->pipefd, 1);
		printf("5\n");
		execve_cmd(px_cmd->cmd[i], &ec_cmd);
	}
	return (0);
}

void			recursive_pipe(char **argv, t_px *px_cmd, int i)
{
	pid_t		pid;
	int			status;
	t_ec		ec_cmd;

	++i;   
	if (i == px_cmd->pipe_cnt)
		last_cmd(px_cmd, &ec_cmd, i);
	else
	{
		hand_over(px_cmd);
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status))
				px_error("pid error\n");
			recursive_pipe(argv, px_cmd, i);
		}
		else if (pid == 0)
		{
			b_connect_pipe(px_cmd->pipefd, 1);
			execve_cmd(px_cmd->cmd[i], &ec_cmd);
		}
	}
}
