/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:45:43 by fbbot             #+#    #+#             */
/*   Updated: 2024/06/26 18:27:08 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tmps;

	i = 0;
	tmps = (char *)s;
	while (i < n)
		tmps[i++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (size && (count > (SIZE_MAX / size)))
		return (NULL);
	result = malloc(size * count);
	if (!result)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && (i < dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = ft_strlen((char *)src);
	return (i);
}
