/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/22 22:41:25 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_error(char *str)
{
	perror(str);
	exit(1);
}

int				redir_input(char *file)
{
	int			fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		px_error("엙 에런데여");
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);	
}

int				redir_output(char *file)
{
	int			fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		px_error("엙 에런데여");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);	
}

void			connect_pipe(int pipefd[2], int num)
{
	dup2(pipefd[num], num);
	close(pipefd[0]);
	close(pipefd[1]);
}

void			init_px_cmd(char **argv, t_px *px_cmd)
{
	px_cmd->infile = argv[1];
	px_cmd->cmd1 = argv[2];
	px_cmd->cmd2 = argv[3];
	px_cmd->outfile = argv[4];
}

void			init_ec_cmd(const char *cmd, t_ec *ec_cmd)
{
	char		**chunk;
	
	printf("3\n");
	//스플릿새끼;;
	chunk = ft_split(cmd, ' ');
	ec_cmd->cmd[0] = ft_strjoin("/bin/", chunk[0]);
	ec_cmd->argv = (char *const *)chunk;
	printf("chunk = %s\n", chunk[0]);
	printf("chunk = %s\n", chunk[1]);
	printf("chunk = %s\n", chunk[2]);
	ec_cmd->envp = NULL;
}

int				main(int argc, char **argv)
{
	t_px		px_cmd;
	t_ec		ec_cmd;
	pid_t		pid;
	int			pipefd[2];

	// if (argc != 5)
	// 	px_error("인자 갯수 안 맞음");
	if (argc == 0) // 테스트용으로 만들엇슴
		px_error("인자 갯수 안 맞음");
	init_px_cmd(argv, &px_cmd);
	pid = fork();
	pipe(pipefd);
	printf("pid = %d\n", pid);
	if (pid > 0)
	{
		// 부모 프로세스 (자식 프로세스 pid 값을 반환)	
		redir_input(argv[2]);
		connect_pipe(pipefd, STDIN_FILENO);
		init_ec_cmd(px_cmd.cmd2, &ec_cmd);
		printf("3\n");
	}
	else if (pid == 0)
	{
		// 자식 프로세스
		redir_output(argv[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
		init_ec_cmd(px_cmd.cmd1, &ec_cmd);
	}
	
	

	return (0);
}