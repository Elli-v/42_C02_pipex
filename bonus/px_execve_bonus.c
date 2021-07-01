/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:07:48 by soooh             #+#    #+#             */
/*   Updated: 2021/07/01 19:08:17 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
