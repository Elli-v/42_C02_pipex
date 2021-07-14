/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:06:28 by soooh             #+#    #+#             */
/*   Updated: 2021/07/14 14:00:00 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	else
	{
		i = 0;
		j = dest_len;
		while (size - dest_len - 1 > 0 && src[i] != '\0')
		{
			dest[j] = src[i];
			j++;
			i++;
			size--;
		}
		dest[j] = '\0';
		return (dest_len + src_len);
	}
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*mem;

	mem = (char *)malloc(ft_strlen(src) + 1);
	if (!mem)
		return (NULL);
	i = 0;
	while (src[i])
	{
		mem[i] = src[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size == 0)
	{
		return (src_len);
	}
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (s1 != 0)
			ft_strdup(s1);
		else if (s1 == 0)
			ft_strdup(s2);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (newstr == 0)
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + 1);
	ft_strlcat(newstr + (s1_len), s2, s2_len + 1);
	return (newstr);
}
