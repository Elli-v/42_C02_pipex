/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:00:37 by soooh             #+#    #+#             */
/*   Updated: 2021/07/08 14:14:51 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	px_error(char *str)
{
	perror(str);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		else
			i++;
	}
	if (s1[i] != '\0' || s2[i] != '\0')
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_px	px_cmd;
	pid_t	pid;

	if (argc < 5)
		px_error("error_invaild_argv");
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
			heredoc_cmd(argv, envp);
		}
		else
			multi_pipe(argc, argv, envp, &px_cmd);
	}
	return (0);
}
