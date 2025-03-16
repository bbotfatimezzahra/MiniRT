/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:53:30 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 12:57:10 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c, int d)
{
	size_t	i;
	int		j;
	size_t	length;

	length = ft_strlen(s);
	i = 0;
	j = 0;
	while (i <= length)
	{
		if ((s[i] == (char)c) && (++j == d))
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_length;

	i = 0;
	if (!dst && dstsize == 0)
		return (ft_strlen(src));
	dst_length = ft_strlen(dst);
	if (dstsize <= dst_length || !dstsize)
		return (dstsize + ft_strlen(src));
	j = dst_length;
	while (src[i] && (j < dstsize - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst_length + ft_strlen(src));
}

char	*ft_strldup(char *s1, size_t length)
{
	char	*s2;

	s2 = (char *) malloc(sizeof(char) * length + 1);
	if (!s2)
		return (NULL);
	s2[0] = '\0';
	ft_strlcat(s2, s1, length + 1);
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	length;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s3 = ft_strldup(s2, ft_strlen(s2));
		free(s2);
		return (s3);
	}
	if (!s2)
		return (ft_strldup(s1, ft_strlen(s1)));
	length = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(length * sizeof(char));
	if (!s3)
	{
		free_everything(&s1, &s2);
		return (NULL);
	}
	s3[0] = '\0';
	ft_strlcat(s3, s1, length);
	ft_strlcat(s3, s2, length);
	free_everything(&s1, &s2);
	return (s3);
}
