#include "minirt.h"

t_tuple	ve_camera(t_ray ray)
{
	return (tu_scale(ray.direction, -1));
}

t_tuple	ve_light(t_tuple o_pos, t_tuple l_pos)
{
	return (tu_subtract(l_pos, o_pos));
}

t_tuple	ve_sp_normal(t_sphere sp, t_tuple w_point)
{
	t_tuple	o_point;
	t_tuple	o_normal;
	t_tuple	w_normal;

	o_point = ma_tu_multiply(ma_invert(sp.transform), w_point);
	o_normal = tu_subtract(o_point, tu_create(0, 0, 0, POINT));
	w_normal = ma_tu_multiply(ma_transpose(ma_invert(sp.transform)), o_normal);
	w_normal.w = 0;
	return (tu_normalize(w_normal));
}

t_tuple	ve_cy_normal(t_cylinder cy, t_tuple w_point)
{
	double	dist;

	dist = pow(w_point.x, 2) + pow(w_point.z, 2);
	if (dist < 1 && w_point.y >= cy.maxy - EPS)
		return (tu_normalize(tu_create(0, 1, 0, VECTOR)));
	else if (dist < 1 && w_point.y <= cy.miny + EPS)
		return (tu_normalize(tu_create(0, -1, 0, VECTOR)));
	return (tu_normalize(tu_create(w_point.x, 0, w_point.z, 1)));
}

t_tuple	ve_reflection(t_tuple in, t_tuple normal)
{
	normal = tu_scale(normal, 2 * tu_dot(in, normal));
	return (tu_subtract(in, normal));
}
