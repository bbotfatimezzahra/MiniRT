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

void	check_elems(t_mini *rt, int *obj, int *light)
{
	int	i;
	int	j;
	char	*c;

	i = -1;
	while (rt->parse_elems[++i])
	{
		c = rt->parse_elems[i];
		if (!ft_isalpha(c[0]) && ft_strncmp(c, "", 2))
			terminate("Incorrect scene file",rt);
		j = 0;
		if (c[0] == 'L')
			(*light)++;
		else if (c[0] != 'A' && c[0] != 'C')
		{
			(*obj)++;
			j++;
		}
		while (!c[++j])
		{
			if(!ft_isdigit(c[j]) && c[j] != 32 && c[j] != ',' 
				&& c[j] != '.' && c[j] != '-')
				terminate("Scene file check error", rt);
		}
	}
}

void	fill_scene(t_mini *rt)
{
	char	**elems;
	int	i;

	elems = rt->parse_elems;
	i = -1;
	while (elems[++i])
	{
		if (!ft_strncmp(elems[i], "A", 1))
			am_create(elems[i], rt);
		else if (!ft_strncmp(elems[i], "C", 1))
			ca_create(elems[i], rt);
		else if (!ft_strncmp(elems[i], "L", 1))
			li_create(elems[i], rt);
		else if (!ft_strncmp(elems[i], "sp", 2))
			sp_parse(elems[i], rt);
		else if (!ft_strncmp(elems[i], "cy", 2))
			cy_parse(elems[i], rt);
		else if (!ft_strncmp(elems[i], "co", 2))
			co_parse(elems[i], rt);
		else if (!ft_strncmp(elems[i], "pl", 2))
			pl_parse(elems[i], rt);
		else if (!ft_strncmp(elems[i], "", 2))
			return ;
		else
			terminate("Scene file elements error 1",rt);
	}
}

void	create_scene(t_mini *rt)
{
	int	light;
	int	obj;

	rt->parse_elems = ft_split(rt->parse_str, '\n', &light);
	if (!rt->parse_elems)
		terminate(ERR_MALLOC, rt);
	light = 0;
	obj = 0;
	check_elems(rt, &obj, &light);
	if (!light)
		terminate("Scene file elements error 2",rt);
	rt->scene.light = ft_calloc(light, sizeof(t_light *));
	if (!rt->scene.light)
		terminate(ERR_MALLOC, rt);
	rt->scene.objs = ft_calloc(obj, sizeof(t_object *));
	if (!rt->scene.objs)
		terminate(ERR_MALLOC, rt);
	fill_scene(rt);
	if (!rt->scene.light || !rt->scene.ambient|| !rt->scene.camera)
		terminate("Scene file elements error 2",rt);
	free(rt->parse_str);
	rt->parse_str = NULL;
	free_double(rt->parse_elems);
	rt->parse_elems = NULL;
}

void	parse_file(char *file, t_mini *rt)
{
	char	*str;
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
	while (str)
	{
		rt->parse_str = ft_strjoin(rt->parse_str, str);
		if (!rt->parse_str)
		{
			close(fd);
			terminate(ERR_MALLOC, rt);
		}
		str = get_next_line(fd);
	}
	create_scene(rt);
}
