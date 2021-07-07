/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:06:56 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 15:43:32 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_px_cmd(char **argv, t_px *px_cmd)
{
	px_cmd->infile = argv[1];
	px_cmd->cmd1 = argv[2];
	px_cmd->cmd2 = argv[3];
	px_cmd->outfile = argv[4];
}

void	connect_pipe(int pipefd[2], int num)
{
	dup2(pipefd[num], num);
	close(pipefd[0]);
	close(pipefd[1]);
}
