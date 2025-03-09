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
	obj->type = PL;
	obj->obj = NULL;
	return (obj);
}

void	pl_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;

	printf("Plane\n");
	infos = ft_split(str, ' ', &length);
	if (length != 4)
	{
		free_double(infos);
		free(str);
		terminate("Incorrect scene file\n", rt);
	}
	obj = pl_create(rt);
	obj->transform = ma_translate(tu_parse(infos[1], 1, rt));
//	obj->transform = ma_multiply(obj->transform,
//			ma_rotate(tu_parse(infos[2], 1, rt)));
	obj->material = m_create(tu_parse(infos[3], 2, rt));
	obj->id = rt->scene.count;
	free_double(infos);
	rt->scene.objs[rt->scene.count] = obj;
	rt->scene.count++;
}
