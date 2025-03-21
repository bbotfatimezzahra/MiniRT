/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_vectors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 02:53:45 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 03:11:48 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	ve_normal_at(t_object *obj, t_tuple point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = ma_tu_multiply(ma_invert(obj->transform), point);
	if (obj->type == SPHERE)
	{
		object_normal = tu_subtract(object_point, tu_create(0, 0, 0, POINT));
		world_normal = ma_tu_multiply(ma_transpose(ma_invert(obj->transform)),
				object_normal);
		world_normal.w = 0;
	}
	else if (obj->type == PLANE)
	{
		object_normal = tu_create(0, 1, 0, VECTOR);
		world_normal = ma_tu_multiply(ma_transpose(ma_invert(obj->transform)),
				object_normal);
		world_normal.w = 0;
	}
	else if (obj->type == CYLINDER)
		ve_cy_normal(object_point, &world_normal, object_normal, *obj);
	else if (obj->type == CONE)
		ve_co_normal(object_point, &world_normal, object_normal, *obj);
	return (tu_normalize(world_normal));
}

void	ve_cy_normal(t_point p, t_vector *wrd_n, t_vector obj_n, t_object obj)
{
	double	dist;

	dist = pow(p.x, 2) + pow(p.z, 2);
	if (dist < 1 && fabs(p.y - 1.f) < EPS)
		obj_n = tu_create(0, 1, 0, POINT);
	else if (dist < 1 && fabs(p.y + 1.f) < EPS)
		obj_n = tu_create(0, -1, 0, 0);
	else
		obj_n = tu_create(p.x, 0, p.z, 0);
	obj_n = tu_normalize(obj_n);
	*wrd_n = ma_tu_multiply(ma_transpose(ma_invert(obj.transform)), obj_n);
	wrd_n->w = 0;
}

void	ve_co_normal(t_point p, t_vector *wrd_n, t_vector obj_n, t_object obj)
{
	double	dist;
	double	y;

	dist = pow(p.x, 2) + pow(p.z, 2);
	if (dist < 1 && fabs(p.y - 1.f) < EPS)
		obj_n = tu_create(0, 1, 0, VECTOR);
	else if (dist < 1 && fabs(p.y + 1.f) < EPS)
		obj_n = tu_create(0, -1, 0, VECTOR);
	else
	{
		y = sqrt(pow(p.x, 2) + pow(p.z, 2));
		if (p.y > 0)
			y = -y;
		obj_n = tu_create(p.x, y, p.z, VECTOR);
	}
	obj_n = tu_normalize(obj_n);
	*wrd_n = ma_tu_multiply(ma_transpose(ma_invert(obj.transform)), obj_n);
	wrd_n->w = 0;
}

t_vector	ve_reflection(t_point in, t_vector normal)
{
	normal = tu_scale(normal, 2 * tu_dot(in, normal));
	return (tu_subtract(in, normal));
}
