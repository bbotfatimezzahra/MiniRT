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

void	check_str(char *str)
{
	int	i;
	int	a;
	char	c;

	i = 0;
	a = 0;
	while (str[i])
	{
		c = str[i];
		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				&& a < 2)
			a++;
		else if (c == '\n')
			a = 0;
		else if ((c < '0' || c > '9') && (c < 9 || c > 13)
				&& c != 32 && c != ',' && c != '.' 
				&& c != '-')
		{
			free(str);
			terminate("Scene file check error", rt);
		}
		i++;
	}
}

void	check_vector(t_tuple tuple, int type, t_mini *rt)
{
	double	min;
	double	max;

	if (type == 0)
	{
		min = -1;
		max = 1;
	}
	else if (type == 2)
	{
		min = 0;
		max = 255;
	}
	else
		return;
	if (tuple.x < min || tuple.x > max
		|| tuple.y < min || tuple.y > max
		|| tuple.z < min || tuple.z > max)
	{
		print_tuple(tuple);
		terminate("Incorrect scene file 1", rt);
	}
}

double	check_ratio(double value, int type, t_mini *rt)
{
	if (type == 2)
		return (value);
	if (value < 0 || (type  == 0 && value > 1)
			|| (type == 1 && value > 180))
		terminate("Incorrect scene file 2", rt);
	return (value);
}

t_tuple	tu_parse(char *str, int type, t_mini *rt)
{
	double	coord[3];
	t_tuple	tuple;

	coord[0] = ft_atod(str);
	coord[1] = ft_atod(&ft_strchr(str, ',', 1)[1]);
	coord[2] = ft_atod(&ft_strchr(str, ',', 2)[1]);
	tuple = tu_create(coord[0], coord[1], coord[2], type);
	check_vector(tuple, type, rt);
	if (type == 2)
		tuple = tu_create(tuple.x/255, tuple.y/255, 
				tuple.z/255, 2);
	return (tuple);
}
	
void	create_scene(char *str, t_mini *rt)
{
	char	**lines;
	int	num;
	int	i;

	check_str(str);
	lines = ft_split(str, '\n', &num);
	if (!lines)
	{
		free(str);
		terminate(ERR_MALLOC, rt);
	}
	rt->scene.objs = ft_calloc(num, sizeof(t_object *));
	if (!rt->scene.objs)
	{
		free(str);
		terminate(ERR_MALLOC, rt);
	}
	i = -1;
	while (++i < num)
	{
		if (!ft_strncmp(lines[i], "A", 1))
			am_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "C", 1))
			ca_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "L", 1))
			li_create(lines[i], rt);
		else if (!ft_strncmp(lines[i], "sp", 2))
			sp_parse(lines[i], rt);
		else if (!ft_strncmp(lines[i], "cy", 2))
			cy_parse(lines[i], rt);
		else if (!ft_strncmp(lines[i], "pl", 2))
			pl_parse(lines[i], rt);
		else if (!ft_strncmp(lines[i], "\n", 1))
			return ;
		else
		{
			free(str);
			free_double(lines);
			printf(" i %d \n", i);
			printf("====== %s \n", lines[i]);
			terminate("Scene file elements error 1",rt);
		}
	}
	free(str);
	free_double(lines);
	if (!rt->scene.light || !rt->scene.ambient|| !rt->scene.camera)
			terminate("Scene file elements error 2",rt);
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
		terminate("Empty scene file", rt);
	scene = NULL;
	while (str)
	{
		scene = ft_strjoin(scene, str);
		if (!scene)
		{
			close(fd);
			terminate(ERR_MALLOC, rt);
		}
		str = get_next_line(fd);
	}
	create_scene(scene, rt);
}
