/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:07:48 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 19:52:15 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

void	init_envp(t_ec *ec_cmd)
{
	char	*path;
	int		i;
	int		j;

	path = "PATH";
	i = -1;
	while (ec_cmd->temp[++i])
	{
		if (ft_strstr(ec_cmd->temp[i], path) != 0)
		{
			ec_cmd->envp_list = &ec_cmd->temp[i];
			j = -1;
			while (ec_cmd->temp[i][++j])
				ec_cmd->envp_list[0][j] = ec_cmd->temp[i][j + 5];
			ec_cmd->envp_list = ft_split(*ec_cmd->envp_list, ':');
			break ;
		}
	}
	i = -1;
	while (ec_cmd->envp_list[++i])
		ec_cmd->envp_list[i] = ft_strjoin(ec_cmd->envp_list[i], "/");
}

void	ex_var(char **chunk)
{
	int		j;
	int		max;

	j = 0;
	if (chunk[1] != 0)
	{
		while (chunk[j++])
			max = j;
		j = 0;
		while (++j != max - 1)
			chunk[j] = ft_strjoin(chunk[j], " ");
		while (j - 1 != 0)
		{
			chunk[j - 1] = ft_strjoin(chunk[j - 1], chunk[j]);
			j--;
		}
		while (++j != max)
			chunk[j] = 0;
		chunk[1] = *ft_split(chunk[1], 39);
	}
}

void	init_ec_cmd(const char *cmd, t_ec *ec_cmd)
{
	char	**chunk;
	int		ret;
	int		i;

	ret = 0;
	chunk = ft_split(cmd, ' ');
	ex_var(chunk);
	init_envp(ec_cmd);
	i = -1;
	while (ec_cmd->envp_list[++i])
	{
		ret = access(ft_strjoin((char *)ec_cmd->envp_list[i], chunk[0]), F_OK);
		if (ret == 0)
		{
			ec_cmd->file = ft_strjoin((char *)ec_cmd->envp_list[i], chunk[0]);
			break ;
		}
	}
	if (ec_cmd->envp_list[i] == (void *)0)
		px_error("command not found");
	ec_cmd->argv = (char *const *)chunk;
	ec_cmd->envp = 0;
}

void	execve_cmd(const char *path, t_ec *ec_cmd)
{
	init_ec_cmd(path, ec_cmd);
	execve((const char *)ec_cmd->file, ec_cmd->argv, ec_cmd->envp);
}
