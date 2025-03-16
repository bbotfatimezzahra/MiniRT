/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:47:19 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 16:50:39 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_object	*co_create(t_mini *rt)
{
	t_object	*obj;
	t_cone		*co;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		terminate(ERR_MALLOC, rt);
	co = ft_calloc(1, sizeof(t_cone));
	if (!co)
		terminate(ERR_MALLOC, rt);
	co->radius = 1;
	co->origin = tu_create(0, 0, 0, POINT);
	co->miny = -1;
	co->maxy = 1;
	co->cap = 0;
	obj->type = CONE;
	obj->material = m_create(tu_create(1, 1, 1, 2));
	obj->transform = ma_identity(4);
	obj->obj = co;
	return (obj);
}

void	co_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char		**infos;
	int			length;
	double		a;

	rt->parse_infos = ft_split(str, ' ', &length);
	if (!rt->parse_infos)
		terminate(ERR_MALLOC, rt);
	infos = rt->parse_infos;
	if (length < 6 || ft_strncmp(infos[0], "co", 3))
		terminate("Incorrect Cone Line", rt);
	obj = co_create(rt);
	rt->scene.objs[rt->scene.count++] = obj;
	a = ft_atod(infos[3], rt, 0) / 2;
	obj->transform = rodrigues_formula(tu_parse(infos[2], 0, rt),
			tu_create(0, 1, 0, VECTOR));
	obj->transform = ma_multiply(ma_scale(tu_create(a,
					ft_atod(infos[4], rt, 0), a, 1)), obj->transform);
	obj->transform = ma_multiply(ma_translate(tu_parse(infos[1], 1, rt)),
			obj->transform);
	obj->material = m_create(tu_parse(infos[5], 2, rt));
	if (length > 6)
		obj->material = m_parse(rt, obj->material, length, 6);
	obj->id = rt->scene.count;
	free_double(&rt->parse_infos);
}
