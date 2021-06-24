/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:05:47 by soooh             #+#    #+#             */
/*   Updated: 2021/06/24 18:06:29 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
