/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 03:12:20 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 03:22:11 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_intersections	intersect_each(t_ray r, t_object *obj)
{
	t_ray			transformed_ray;
	t_intersections	xs;

	xs.count = 0;
	transformed_ray = ray_transform(r, ma_invert(obj->transform));
	if (obj->type == SPHERE)
		return (sp_intersect(obj, transformed_ray, xs));
	if (obj->type == CYLINDER)
		return (cy_intersect(obj, transformed_ray, xs));
	else if (obj->type == PLANE)
		return (pl_intersect(transformed_ray, obj));
	else if (obj->type == CYLINDER)
		return (cy_intersect(obj, transformed_ray, xs));
	else if (obj->type == CONE)
		return (co_intersect(obj, transformed_ray, xs));
	return (xs);
}

t_intersect	hit(t_intersections xs)
{
	int			i;
	t_intersect	hit;

	hit.t = -1;
	hit.object = NULL;
	if (!xs.count)
		return (hit);
	i = xs.count - 1;
	while (i >= 0)
	{
		if ((hit.t < 0 || hit.t > xs.inter[i].t) && xs.inter[i].t > EPS)
			hit = xs.inter[i];
		i--;
	}
	return (hit);
}

t_intersections	intersect_world(t_scene s, t_ray r)
{
	t_intersections	world_xs;
	t_intersections	obj_xs;
	int				i;
	int				j;

	i = 0;
	world_xs.count = 0;
	obj_xs.count = 0;
	while (i < s.count)
	{
		obj_xs = intersect_each(r, s.objs[i]);
		if (obj_xs.count != 0)
		{
			j = 0;
			while (j < obj_xs.count && world_xs.count < 1024)
			{
				world_xs.inter[world_xs.count] = obj_xs.inter[j];
				world_xs.count++;
				j++;
			}
		}
		i++;
	}
	return (world_xs);
}
