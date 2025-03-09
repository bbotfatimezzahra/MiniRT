/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:47:08 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 18:03:20 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	new_line(int fd, char **line)
{
	ssize_t		i;

	*line = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!*line)
		return (-1);
	i = read(fd, *line, BUFFER_SIZE);
	if (i != -1)
		line[0][i] = '\0';
	return (i);
}

void	free_everything(char **buffer, char **str)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*str)
		free(*str);
}

char	*get_the_line(char **buffer, int i)
{
	char	*line;
	char	*temp;

	while (buffer[0][i] != '\n')
		i++;
	line = ft_strldup(*buffer, i + 1);
	if (!line)
	{
		free_everything(buffer, &line);
		return (NULL);
	}
	temp = *buffer;
	if (!buffer[0][++i])
		*buffer = NULL;
	else
	{
		*buffer = ft_strldup(&buffer[0][i], ft_strlen(&buffer[0][i]));
		if (!*buffer)
		{
			free_everything(&temp, &line);
			return (NULL);
		}
	}
	free(temp);
	return (line);
}

ssize_t	fill_buffer(int fd, char **buffer, char **line)
{
	ssize_t	i;

	i = new_line(fd, line);
	if ((i == -1) || (!i && !*buffer))
	{
		free_everything(buffer, line);
		return (-1);
	}
	if (i && *buffer)
	{
		*buffer = ft_strjoin(*buffer, *line);
		if (!*buffer)
			return (-1);
	}
	else if (i && !*buffer)
	{
		*buffer = ft_strldup(*line, ft_strlen(*line));
		free(*line);
		if (!*buffer)
			return (-1);
	}
	else
		free(*line);
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	ssize_t		i;

	if (fd < 0)
		return (NULL);
	i = 1;
	while (i)
	{
		i = fill_buffer(fd, &buffer, &line);
		if (i == -1)
			return (close(fd), NULL);
		if (buffer && ft_strchr(buffer, '\n', 1))
			return (get_the_line(&buffer, 0));
	}
	if (!i && buffer)
	{
		line = ft_strldup(buffer, ft_strlen(buffer));
		free(buffer);
		buffer = NULL;
		if (!line)
			return (close(fd), NULL);
		return (line);
	}
	return (0);
}
