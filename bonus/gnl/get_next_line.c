/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 19:25:36 by soooh             #+#    #+#             */
/*   Updated: 2021/06/26 02:37:41 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					find_n(char *backup)
{
	int		i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int					div_line(char **backup, char **line, int idx_num)
{
	char		*temp;
	int			len;

	(*backup)[idx_num] = '\0';
	*line = gnl_strdup(*backup);
	len = gnl_strlen(*backup + idx_num + 1);
	if (len == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	temp = gnl_strdup(*backup + idx_num + 1);
	free(*backup);
	*backup = temp;
	return (1);
}

int					onandon(char **backup, char **line, int save_str)
{
	int		idx_num;

	if (save_str < 0)
		return (-1);
	if (*backup && (idx_num = find_n(*backup)) >= 0)
		return (div_line(backup, line, idx_num));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = gnl_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*backup[OPEN_MAX];
	int				save_str;
	int				idx_num;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	while ((save_str = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[save_str] = '\0';
		backup[fd] = gnl_strjoin(backup[fd], buffer);
		if ((idx_num = find_n(backup[fd])) >= 0)
			return (div_line(&backup[fd], line, idx_num));
	}
	return (onandon(&backup[fd], line, save_str));
}

int		px_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*px_strjoin(char *s1, char *s2)
{
	int		i;
	char	*buf;

	if (!(buf = malloc(sizeof(char) * (px_strlen(s1) + px_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*s1)
		buf[i++] = *s1++;
	while (*s2)
		buf[i++] = *s2++;
	buf[i] = '\0';
	return (buf);
}

int					px_gnl(char **line)
{
	int		size;
	char	buf[2];
	char	*store;
	char	*temp;

	size = 1;
	store = px_strjoin("", "");
	buf[size] = '\0';
	while (size && buf[0] != '\n')
	{
		size = read(0, buf, 1);
		if (size <= 0)
			return (0);
		if (buf[0] != '\n' && size != 0)
		{
			temp = px_strjoin(store, buf);
			free(store);
			store = temp;
		}
	}
	*line = store;
	return (size);
}