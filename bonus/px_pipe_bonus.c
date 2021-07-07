/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:06:56 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 20:05:13 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			hand_over(t_px *px_cmd)
{
	px_cmd->prev_pipefd[0] = px_cmd->pipefd[0];
	px_cmd->prev_pipefd[1] = px_cmd->pipefd[1];
	b_connect_pipe(px_cmd->prev_pipefd, 0);
	pipe(px_cmd->pipefd);
}

void			init_px_cmd(int argc, char **argv, t_px *px_cmd)
{
	int			n;
	int			i;

	i = -1;
	n = argc - 3;
	px_cmd->infile = argv[1];
	px_cmd->outfile = argv[argc - 1];
	px_cmd->cmd = malloc(sizeof(int *) * n);
	while (++i < n)
		px_cmd->cmd[i] = argv[i + 2];
	px_cmd->pipe_cnt = n - 1;
}

void			connect_pipe(int pipefd[2], int num)
{
	dup2(pipefd[num], num);
	close(pipefd[0]);
	close(pipefd[1]);
}

void			close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void			b_connect_pipe(int pipefd[2], int num)
{
	dup2(pipefd[num], num);
	close_pipe(pipefd);
}
