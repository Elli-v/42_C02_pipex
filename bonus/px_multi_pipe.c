/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_multi_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 03:59:27 by soooh             #+#    #+#             */
/*   Updated: 2021/07/14 01:01:16 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	hand_over(t_px *px_cmd)
{
	px_cmd->prev_pipefd[0] = px_cmd->pipefd[0];
	px_cmd->prev_pipefd[1] = px_cmd->pipefd[1];
	b_connect_pipe(px_cmd->prev_pipefd, 0);
	pipe(px_cmd->pipefd);
}

void	last_cmd(t_px *px_cmd, t_ec *ec_cmd, char **envp, int i)
{
	redir_output(px_cmd->outfile);
	b_connect_pipe(px_cmd->pipefd, 0);
	execve_cmd(px_cmd->cmd[i], ec_cmd, envp);
}


int	multi_pipe(int argc, char **argv, char **envp, t_px *px_cmd)
{
	pid_t	pid;
	int		status;
	t_ec	ec_cmd;
	int		i;

	i = 0;
	init_px_cmd(argc, argv, px_cmd);
	pipe(px_cmd->pipefd);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			px_error("pid error\n");
		close_pipe(px_cmd->prev_pipefd);
		recursive_pipe(argv, px_cmd, envp, i);
	}
	else if (pid == 0)
	{
		redir_input(px_cmd->infile);
		b_connect_pipe(px_cmd->pipefd, 1);
		execve_cmd(px_cmd->cmd[i], &ec_cmd, envp);
	}
	return (0);
}

void	recursive_pipe(char **argv, t_px *px_cmd, char  **envp, int i)
{
	pid_t	pid;
	int		status;
	t_ec	ec_cmd;

	++i;   
	if (i == px_cmd->pipe_cnt)
		last_cmd(px_cmd, &ec_cmd, envp, i);
	else
	{
		hand_over(px_cmd);
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status))
				px_error("pid error\n");
			recursive_pipe(argv, px_cmd, envp, i);
		}
		else if (pid == 0)
		{
			b_connect_pipe(px_cmd->pipefd, 1);
			execve_cmd(px_cmd->cmd[i], &ec_cmd, envp);
		}
	}
}
