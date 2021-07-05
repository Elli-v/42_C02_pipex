/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/07/05 20:53:14 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void			px_error(char *str)
{
	perror(str);
	exit(1);
}

int				main(int argc, char **argv, char **envp)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];
	// char		**loona;
	// int			i;
	// int			j;
	// char		*pa;
	// int			ret;
	
	// i = -1;
	// pa = "PATH";
	// while (++i < 10)
	// {
	// 	j = -1;
	// 	while (++j < 4)
	// 	{
	// 		ret = ft_strcmp(&envp[i][j], &pa[j]);
	// 		if (ret == 61)
	// 			loona = &envp[i];
	// 	}
	// }
	// i = -1;
	// while (envp[3][++i])
	// 	loona[0][i] = envp[3][i + 5];
	// loona = ft_split(*loona, ':');

	if (argc != 5)
		px_error("error_invaild_argv");
	init_px_cmd(argv, &px_cmd);
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		redir_output(px_cmd.outfile);
		connect_pipe(pipefd, 0);
		execve_cmd(px_cmd.cmd2, &ec_cmd, envp);
	}
	else if (pid == 0)
	{
		redir_input(px_cmd.infile);
		connect_pipe(pipefd, 1);
		execve_cmd(px_cmd.cmd1, &ec_cmd, envp);
	}
	return (0);
}
