/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:18:39 by soooh             #+#    #+#             */
/*   Updated: 2021/07/07 15:57:08 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;
	size_t			i;

	i = 0;
	total_size = count * size;
	ptr = (unsigned char *)malloc(total_size);
	if (!ptr)
		return (0);
	while (i < total_size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

static int	ft_wcount(char const *s, char c)
{
	int		flag;
	int		n;

	n = 0;
	flag = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s++ == c)
		{
			if (flag == 1)
			{
				n++;
				flag = 0;
			}
		}
		else
			flag = 1;
	}
	if (flag == 1)
		n++;
	return (n);
}

static char	*ft_wlen(int *a, const char *s, char c)
{
	int		i;
	int		k;
	char	*ret;

	i = 0;
	while (s[*a + i] && s[*a + i] != c)
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (ret == 0)
		return (0);
	ret[i] = 0;
	*a += i;
	k = 0;
	while (--i >= 0)
		ret[i] = s[*a - ++k];
	return (ret);
}

static char	*ft_return(char **ret)
{
	int		n;

	n = 0;
	while (ret[n])
		free(ret[n++]);
	free(ret);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		k;
	int		i;
	int		n;

	n = ft_wcount(s, c);
	ret = (char **)ft_calloc((n + 1), sizeof(char *));
	if (ret == 0)
		return (0);
	i = -1;
	k = 0;
	while (++i < n)
	{
		while (s[k] && s[k] == c)
			k++;
		ret[i] = ft_wlen(&k, s, c);
		if (ret[i] == 0)
			ft_return(ret);
	}
	return (ret);
}
