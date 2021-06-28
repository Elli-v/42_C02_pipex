/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/29 01:55:38 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			px_error(char *str)
{
	perror(str);
	exit(1);
}


void			bonus_init_px_cmd(char **argv, t_px *px_cmd, int argc)
{
	int			n;
	int			i;

	i = 0;
	n = argc - 2;
	px_cmd->infile = argv[1];
	px_cmd->outfile = argv[argc - 1];
	while (++i != n)
		px_cmd->cmd[i] = argv[i + 1];
	px_cmd->cmd_cnt = i - 1;
}

void			multi_pipe(int argc, char ** argv, t_px *px_cmd)
{
	pid_t		pid;
	int			pipefd[2];

	bonus_init_px_cmd(argv, px_cmd, argc);
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		
	}
	else if (pid == 0)
	{
		
	}
}

int				main(int argc, char **argv)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];

	if (argc < 5)
		px_error("인자 갯수 안 맞음");
	// pipe(pipefd);
	// pid = fork();
	// if (pid > 0)
	// {
	// 	if (ft_strcmp(argv[1], "heredoc") == 0)
	// 	{
	// 		redir_output(argv[5]);
	// 		connect_pipe(pipefd, 0);
	// 		execve_cmd(argv[4], &ec_cmd);
	// 	}
	// 	else
	// 	{
	// 		redir_output(argv[4]);
	// 		connect_pipe(pipefd, 0);
	// 		execve_cmd(argv[3], &ec_cmd);
	// 	}
	// }
	// else if (pid == 0)
	// {
	// 	if (ft_strcmp(argv[1], "heredoc") == 0)
	// 	{
	// 		heredoc(argv);
	// 		redir_input("./temp");
	// 		clear_temp();
	// 		connect_pipe(pipefd, 1);
	// 		execve_cmd(argv[3], &ec_cmd);
	// 	}
	// 	else
	// 	{
	// 		
	// 		redir_input(argv[1]);
	// 		connect_pipe(pipefd, 1);
	// 		execve_cmd(argv[2], &ec_cmd);
	// 	}
	// }
	multi_pipe(argc, argv, &px_cmd);
	printf("whyyyyy-\n");
	return (0);
}
