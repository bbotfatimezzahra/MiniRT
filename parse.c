/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:55:54 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 19:20:49 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_str(char *str)
{
	int	i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				&& i < 2)
			i++;
		else if ((c < '0' || c > '9') && (c < 9 || c > 13)
				&& c != 32 && c != ',' && c != '.' && c != '-')
			return (0);
		i++;
	}
	return (1);
}

t_tuple	tu_parse(char *str, int type)
{
	double	coord[3];

	coord[0] = ft_atod(str);
	coord[1] = ft_atod(&ft_strchr(str, ',', 1)[1]);
	coord[2] = ft_atod(&ft_strchr(str, ',', 2)[1]);
	return (tu_create(coord[0], coord[1], coord[2], type));
}
	
void	create_scene(char *str, t_mini *rt)
{
	char	**lines;
	int	num;

	if (!check_str(str))
	{
		free(str);
		terminate("Scene file check error", rt);
	}
	lines = ft_split(str, '\n', &num);
	if (!lines)
	{
		free(str);
		terminate(ERR_MALLOC, rt);
	}
	rt->scene.objs = ft_calloc(sizeof(t_object *) * num);
	if (!rt->scene.objs)
	{
		free(str);
		terminate(ERR_MALLOC, rt);
	}
	i = 0;
	while (i < num)
	{
		//if (!ft_strncmp(lines[i], "A", 1))
		//	al_create(lines[i], rt);
		if (!ft_strncmp(lines[i], "C", 1))
			ca_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "L", 1))
			li_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "sp", 2))
			sp_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "cy", 2))
			cy_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "pl", 2))
			pl_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "\n", 1))
			return ;
		else
		{
			free(str);
			free_double(lines);
			terminate("Scene file elements error",rt);
		}
		i++;
	}
	free(str);
	free_double(lines);
	print_tuple(rt->scene.light.position);
	print_tuple(rt->scene.light.intensity);
	printf("count : %d \n",rt->scene.light.count);

}

void	parse(char *file, t_mini *rt)
{
	char	*str;
	char	*scene;
	int		fd;

	str = ft_strchr(file, '.', 1);
	if (!str || ft_strncmp(str, ".rt", 4))
		terminate(ERR_USAGE, rt);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate("Open failure", rt);
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		terminate("Empty scene file", rt);
	}
	scene = NULL;
	while (str)
	{
		scene = ft_strjoin(scene, str);
		if (!scene)
		{
			close(fd);
			terminate(ERR_MALOC, rt);
		}
		str = get_next_line(fd);
	}
	close(fd);
	create_scene(scene, rt);
}
