#include "minirt.h"

t_vector	ve_camera(t_ray ray)
{
	return (tu_scale(ray.direction, -1));
}

t_vector	ve_light(t_point o_pos, t_point l_pos)
{
	return (tu_subtract(l_pos, o_pos));
}

t_vector	ve_sp_normal(t_object *sp, t_point w_point)
{
	t_point	o_point;
	t_vector	o_normal;
	t_vector	w_normal;

	o_point = ma_tu_multiply(ma_invert(sp->transform), w_point);
	o_normal = tu_subtract(o_point, tu_create(0, 0, 0, POINT));
	w_normal = ma_tu_multiply(ma_transpose(ma_invert(sp->transform)), o_normal);
	w_normal.w = 0;
	return (tu_normalize(w_normal));
}

t_vector	ve_cy_normal(t_object *cy, t_point w_point)
{
	double	dist;
	t_cylinder	*obj;

	obj = (t_cylinder *)cy;
	dist = pow(w_point.x, 2) + pow(w_point.z, 2);
	if (dist < 1 && w_point.y >= obj->maxy - EPS)
		return (tu_normalize(tu_create(0, 1, 0, VECTOR)));
	else if (dist < 1 && w_point.y <= obj->miny + EPS)
		return (tu_normalize(tu_create(0, -1, 0, VECTOR)));
	return (tu_normalize(tu_create(w_point.x, 0, w_point.z, 1)));
}

t_vector	ve_reflection(t_point in, t_vector normal)
{
	normal = tu_scale(normal, 2 * tu_dot(in, normal));
	return (tu_subtract(in, normal));
}
