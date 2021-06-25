/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soooh <soooh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 01:09:59 by soooh             #+#    #+#             */
/*   Updated: 2021/06/26 02:25:50 by soooh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		gnl_strlen(const char *str)
{
	int		len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t		gnl_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (src_len);
}

size_t		gnl_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	dest_len = gnl_strlen(dest);
	src_len = gnl_strlen(src);
	i = 0;
	while (src[i] != '\0' && dest_len + 1 + i < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	if (size < dest_len)
		return (size + src_len);
	return (dest_len + src_len);
}

char		*gnl_strdup(const char *src)
{
	size_t	i;
	char	*mem;

	mem = (char *)malloc(gnl_strlen(src) + 1);
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

char		*gnl_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? gnl_strdup(s2) : gnl_strdup(s1));
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	if (!(newstr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	gnl_strlcpy(newstr, s1, s1_len + 1);
	// free(s1);
	gnl_strlcat(newstr + (s1_len), s2, s2_len + 1);
	return (newstr);
}
