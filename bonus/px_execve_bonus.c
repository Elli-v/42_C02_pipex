/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_execve_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:07:48 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 20:11:17 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = -1;
	if (to_find[0] == '\0')
		return (str);
	printf("10\n");
	printf ("str = %s\n", to_find);
	while (str[++i])
	{
		j = 0;
		printf("i = %d\n", i);
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
	}
	return (0);
}

void	init_envp(t_ec *ec_cmd)
{
	char	*path;
	int		i;
	int		j;

	char	*temp;
	temp = 0;

	path = "PATH";
	i = -1;
	while (ec_cmd->temp[++i])
	{
		printf("i = %d\n", i);
		temp = ft_strstr(ec_cmd->temp[i], path);
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
		printf("ㅇㅏㄴ냐루\n");
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

void			init_ec_cmd(const char *cmd, t_ec *ec_cmd)
{
	char		**chunk;
	int		ret;
	int		i;

	ret = 0;
	printf("8\n");
	printf("asdasdasd = %s\n", cmd);
	ex_var(chunk);
	printf("9\n");
	init_envp(ec_cmd);
	printf("10\n");
	i = -1;
	// ec_cmd->cmd[0] = ft_strjoin("/usr/local/bin/", chunk[0]);
	// ec_cmd->cmd[1] = ft_strjoin("/usr/bin/", chunk[0]);
	// ec_cmd->cmd[2] = ft_strjoin("/bin/", chunk[0]);
	// ec_cmd->cmd[3] = ft_strjoin("/usr/sbin/", chunk[0]);
	// ec_cmd->cmd[4] = ft_strjoin("/sbin/", chunk[0]);
	// while (ec_cmd->envp_list[++i])
	// {
	// 	printf("%s\n", ec_cmd->envp_list[i]);
	// }
	while (ec_cmd->envp_list[++i])
	{
		ret = access(ft_strjoin((char *)ec_cmd->envp_list[i], chunk[0]), F_OK);
		if (ret == 0)
		{
			ec_cmd->file = ft_strjoin((char *)ec_cmd->envp_list[i], chunk[0]);
			break ;
		}
	}
	printf("11\n");
	if (ec_cmd->envp_list[i] == (void *)0)
		px_error("command not found");
	ec_cmd->argv = (char *const *)chunk;
	ec_cmd->envp = 0;
}

void			execve_cmd(const char *path, t_ec *ec_cmd)
{
	int			i;

	i = -1;
	printf("7\n");
	// printf ("temp = %s\n", ec_cmd->temp);
	init_ec_cmd(path, ec_cmd);
	// while (i < 5)
		execve(ec_cmd->file, ec_cmd->argv, ec_cmd->envp);
	px_error("command not found");
}
