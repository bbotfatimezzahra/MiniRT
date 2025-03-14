/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:02:45 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 15:55:57 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*pl_create(t_mini *rt)
{
	t_object	*obj;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		terminate(ERR_MALLOC, rt);
	obj->material = m_create(tu_create(1, 1, 1, 2));
	obj->transform = ma_identity(4);
	obj->type = PLANE;
	obj->obj = NULL;
	return (obj);
}

void	pl_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;

	printf("Plane\n");
	rt->parse_infos = ft_split(str, ' ', &length);
	infos = rt->parse_infos;
	if (length != 4 || ft_strncmp(infos[0], "pl", 3))
		terminate("Incorrect scene file\n", rt);
	obj = pl_create(rt);
	rt->scene.objs[rt->scene.count++] = obj;
	obj->transform = rodrigues_formula(tu_normalize(tu_parse(infos[2], 0, rt)), tu_create(0, 1, 0, 0));
  obj->transform = ma_multiply(ma_translate(tu_parse(infos[1], 1, rt))
                               , obj->transform);
	obj->material = m_create(tu_parse(infos[3], 2, rt));
	obj->id = rt->scene.count;
	free_double(rt->parse_infos);
	rt->parse_infos = NULL;
}
