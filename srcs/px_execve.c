/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:07:48 by soooh             #+#    #+#             */
/*   Updated: 2021/07/05 21:00:00 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_strcmp(const char *s1, const char *s2)
 {
 	int	i;
 
 	i = 0;
 	while (s1[i] == s2[i] && s1[i] && s2[i])
 		i++;
 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void			init_ec_envp(t_ec *ec_cmd, char **envp)
{
	int			i;
	int			j;
	char		*pa;
	int			ret;

	i = -1;
	pa = "PATH";
	while (++i < 10)
	{
		j = -1;
		while (++j < 4)
		{
			ret = ft_strcmp(&envp[i][j], &pa[j]);
			if (ret == 61)
				*ec_cmd->envp = &envp[i];
		}
	}
	i = -1;
	while (envp[3][++i])
		*ec_cmd->envp[0][i] = envp[3][i + 5];
	// *ec_cmd->envp = ft_split(ec_cmd->envp, ':');
	printf(">>>>>>%s\n", *ec_cmd->envp[0]);
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
}

void			execve_cmd(const char *path, t_ec *ec_cmd, char **envp)
{
	int			i;

	i = -1;
	init_ec_cmd(path, ec_cmd);
	while (i < 5)
		execve(ec_cmd->cmd[++i], ec_cmd->argv, *ec_cmd->envp);
	px_error("command not found");
}
