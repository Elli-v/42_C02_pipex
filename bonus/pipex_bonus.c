/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/07/01 03:59:49 by soooh            ###   ########.fr       */
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
	pid_t		pid;
	t_fd		pipefd;
	
	if (argc < 5)
		px_error("인자 갯수 안 맞음");
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		if (ft_strcmp(argv[1], "heredoc") == 0)
			clear_temp();
		exit(0);
	}
	else if (pid == 0)
	{
		if (ft_strcmp(argv[1], "heredoc") == 0)
		{
			heredoc(argv);
			heredoc_cmd(argv);
		}
		else
			multi_pipe(argc, argv, &px_cmd);
	}
	return (0);
}