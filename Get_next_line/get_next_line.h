/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:43:57 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 18:03:21 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
ssize_t	fill_buffer(int fd, char **buffer, char **line);
char	*get_the_line(char **buffer, int i);
void	free_everything(char **buffer, char **str);
ssize_t	new_line(int fd, char **line);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c, int d);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strldup(char *s, size_t length);
char	*ft_strjoin(char *s1, char *s2);

#endif
