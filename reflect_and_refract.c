#include "minirt.h"

t_color reflect_color(t_compute cmp, t_scene s, int reflect_recur_checker)
{
  t_ray reflect_ray;
  t_color clr;

  reflect_recur_checker++;
  if (cmp.obj->material.reflective < EPS || reflect_recur_checker > 2)
    return (tu_create(0, 0, 0, COLOR));
  reflect_ray.origin = cmp.above_point;
  reflect_ray.direction = cmp.reflectv;
  clr = color_at(s, reflect_ray, reflect_recur_checker);
  return (tu_scale(clr, cmp.xs.object->material.reflective));
}


t_color refracted_color(t_scene s, t_compute cmp, int recursive_limit)
{
  (void) s;
  if (cmp.obj->material.transparency < EPS || recursive_limit == 0)
    return (tu_create(0, 0, 0, COLOR));
  else
    return (tu_create(1, 1, 1, COLOR));
}
