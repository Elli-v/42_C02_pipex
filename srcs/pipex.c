/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/24 02:19:25 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void			connect_pipe(int pipefd[2], int num)
{
	dup2(pipefd[num], num);
	close(pipefd[0]);
	close(pipefd[1]);
}

void			redir_input(char *file)
{
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		px_error("엙 에런데여");
	dup2(fd, 0);
	close(fd);
}

void			redir_output(char *file)
{
	int			fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		px_error("엙 에런데여");
	dup2(fd, 1);
	close(fd);
}

void			init_px_cmd(char **argv, t_px *px_cmd)
{
	px_cmd->infile = argv[1];
	px_cmd->outfile = argv[4];
	px_cmd->cmd1 = argv[2];
	px_cmd->cmd2 = argv[3];
}

void			init_ec_cmd(const char *cmd, t_ec *ec_cmd)
{
	char		**chunk;
	
	chunk = ft_split(cmd, ' ');
	ec_cmd->cmd[0] = ft_strjoin("/usr/local/bin/", chunk[0]);
	ec_cmd->cmd[1] = ft_strjoin("/usr/bin/", chunk[0]);
	ec_cmd->cmd[2] = ft_strjoin("/bin/", chunk[0]);
	ec_cmd->cmd[3] = ft_strjoin("/usr/sbin/", chunk[0]);
	ec_cmd->cmd[4] = ft_strjoin("/sbin/", chunk[0]);
	ec_cmd->argv = (char *const *)chunk;
	ec_cmd->envp = 0;
}

void			execve_cmd(const char *path, t_ec *ec_cmd)
{
	int			i;

	i = -1;
	init_ec_cmd(path, ec_cmd);
	while (i < 5) 
		execve(ec_cmd->cmd[++i], ec_cmd->argv, ec_cmd->envp);
}

int				main(int argc, char **argv)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];
	int			status;

	
	if (argc != 5)
		px_error("인자 갯수 안 맞음");
	init_px_cmd(argv, &px_cmd);
	pipe(pipefd);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) == 0)
			exit(1);
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