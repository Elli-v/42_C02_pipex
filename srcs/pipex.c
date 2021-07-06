/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 04:58:30 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

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
	char		**i;
	int			j;
	int			max;

	j = 0;
	if (argc != 5)
		px_error("error_invaild_argv");
	init_px_cmd(argv, &px_cmd);





	// i = ft_split(px_cmd.cmd1, ' ');
	// if (ft_strstr(i[1], "'") != 0)
	// {
	// 	while (i[j++])
	// 		max = j;
	// 	j = 0;
	// 	while (++j != max - 1)
	// 		i[j] = ft_strjoin(i[j], " ");
	// 	printf("j = %d\n", j);
	// 	while (j - 1 != 0)
	// 	{
	// 		i[j - 1] = ft_strjoin(i[j - 1], i[j]);
	// 		j--;
	// 	}
	// 	printf("j = %d\n", j);
	// 	while (++j != max)
	// 		i[j] = 0;
	// 	i[1] = *ft_split(i[1], 39);
	// }
	// printf("i[%d] = %s****\n", j, i[1]);
	// printf("i[%d] = %s****\n", j, i[2]);
	// printf("i[%d] = %s****\n", j, i[3]);






	ec_cmd.temp = envp;
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
