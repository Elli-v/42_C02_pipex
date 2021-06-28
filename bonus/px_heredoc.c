/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 22:35:36 by soooh             #+#    #+#             */
/*   Updated: 2021/06/29 00:05:59 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void			clear_temp(void)
{
	char **argv;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "-f";
	argv[1] = "./temp";
	argv[2] = NULL;
	if (fork() == 0)
		execve("/bin/rm", (char *const *)argv, NULL);
}

int				heredoc(char **argv)
{
	int			fd;
	char		*buf;
	int			i;

	i = 1;
	buf = 0;
	fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		px_error("임시 파일에 문제 생김;;");
	write(STDOUT_FILENO, "heredoc> ", 9);
	while ((i = px_gnl(0, &buf)) > 0)
	{
		if (ft_strcmp(buf, argv[2]) == 0)
		{
			close(fd);
			return (0);
		}			
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		write(STDOUT_FILENO, "heredoc> ", 9);
	}
	close(fd);
	return (0);
}