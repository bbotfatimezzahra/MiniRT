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

void	check_str(t_mini *rt)
{
	int	i;
	int	a;
	char	c;

	i = 0;
	a = 0;
	while (rt->parse_str[i])
	{
		c = rt->parse_str[i];
		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				&& a < 2)
			a++;
		else if (c == '\n')
			a = 0;
		else if ((c < '0' || c > '9') && (c < 9 || c > 13)
				&& c != 32 && c != ',' && c != '.' 
				&& c != '-')
			terminate("Scene file check error", rt);
		i++;
	}
}
void	fill_scene(t_mini *rt, int num)
{
	char	**elems;
	int	i;

	elems = rt->parse_elems;
	i = -1;
	while (++i < num)
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
		else if (!ft_strncmp(elems[i], "pl", 2))
			pl_parse(elems[i], rt);
		else if (!ft_strncmp(elems[i], "\n", 1))
			return ;
		else
			terminate("Scene file elements error 1",rt);
	}
}

void	create_scene(t_mini *rt)
{
	int	num;

	check_str(rt);
	rt->parse_elems = ft_split(rt->parse_str, '\n', &num);
	if (!rt->parse_elems)
		terminate(ERR_MALLOC, rt);
	rt->scene.objs = ft_calloc(num, sizeof(t_object *));
	if (!rt->scene.objs)
		terminate(ERR_MALLOC, rt);
	fill_scene(rt, num);
	if (!rt->scene.light || !rt->scene.ambient|| !rt->scene.camera)
		terminate("Scene file elements error 2",rt);
	free(rt->parse_str);
	rt->parse_str = NULL;
	free_double(rt->parse_elems);
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
