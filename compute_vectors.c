#include "minirt.h"

t_vector	ve_camera(t_ray ray)
{
	return (tu_scale(ray.direction, -1));
}

t_vector	ve_light(t_point o_pos, t_point l_pos)
{
	return (tu_subtract(l_pos, o_pos));
}


t_tuple  ve_normal_at(t_object *obj, t_tuple point)
{
  t_tuple object_point;
  t_tuple object_normal;
  t_tuple world_normal;

  object_point = ma_tu_multiply(ma_invert(obj->transform) , point);
  if (obj->type == SPHERE)
  {
    object_normal = tu_subtract(object_point, tu_create(0, 0, 0, POINT));
    world_normal = ma_tu_multiply(ma_transpose(ma_invert(obj->transform)), object_normal);
    world_normal.w = 0;
  }
  else if (obj->type == PLANE)
  {
    object_normal = tu_create(0, 1, 0, VECTOR); 
    world_normal = ma_tu_multiply(ma_transpose(ma_invert(obj->transform)), object_normal);
    world_normal.w = 0;
  }
  else if (obj->type == CYLINDER)
    ve_cy_normal(object_point, &world_normal, object_normal, *obj);
  return (tu_normalize(world_normal));
}


void	ve_cy_normal(t_point obj_point, t_vector *wrd_n, t_vector obj_n, t_object obj)
{
	if (fabs(obj_point.y - 1.f) < EPS)
	  obj_n = tu_create(0, 1, 0, VECTOR);
	else if (fabs(obj_point.y + 1.f) < EPS)
	  obj_n = tu_create(0, -1, 0, VECTOR);
	else
	  obj_n = tu_create(obj_point.x, 0, obj_point.z, 0);
	obj_n = tu_normalize(obj_n);
	*wrd_n = ma_tu_multiply(ma_transpose(ma_invert(obj.transform)), obj_n);
	wrd_n->w = 0;
}

t_vector	ve_reflection(t_point in, t_vector normal)
{
	normal = tu_scale(normal, 2 * tu_dot(in, normal));
	return (tu_subtract(in, normal));
}

