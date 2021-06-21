/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/06/22 02:33:17 by soooh            ###   ########.fr       */
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

int				main(int argc, char **argv)
{
	pid_t		pid;
	int			pipefd[2];

	// if (argc != 5)
	// 	px_error("인자 갯수 안 맞음");
	if (argc == 0) // 테스트용으로 만들엇슴
		px_error("인자 갯수 안 맞음");
	pid = fork();
	pipe(pipefd);
	if (pid > 0)
	{
		// 부모 프로세스 (자식 프로세스 pid 값을 반환)	
		redir_output(argv[2]);
		connect_pipe(pipefd, STDIN_FILENO);
	}
	else if (pid == 0)
	{
		// 자식 프로세스
		redir_input(argv[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
	}
	
	

	return (0);
}