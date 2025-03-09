#include "minirt.h"

t_pattern new_pattern(t_color a, t_color b, t_pattern_type type)
{
  t_pattern new;

  new.enable = true;
  new.type = type;
  new.a = a;
  new.b = b;
  new.transformation = ma_identity(4);
  return (new);
}

t_color strip_pattern(t_pattern pat, t_point point)
{
  if ((int)round(point.x) % 2 == 0)
    return (pat.a);
  return (pat.b);
}


t_color gradient_pattern(t_pattern pat, t_point point)
{
  t_color distance;
  double  fraction;

  distance = tu_subtract(pat.b , pat.a);
  fraction = point.x - floor(point.x);

  return (tu_add(pat.a, tu_scale(distance, fraction)));
}

t_color ring_pattern(t_pattern pat, t_point point)
{
  if ((int)floor(sqrt(pow(point.x, 2) + pow(point.z, 2))) % 2 == 0)
    return(pat.a);
  return (pat.b);
}


t_color pattern_obj(t_pattern pat, t_object obj, t_point point)
{
  t_point pattern_point;
  t_point obj_point;

  obj_point = ma_tu_multiply(obj.transform, point);
  pattern_point = ma_tu_multiply(pat.transformation, obj_point);
  if (pat.type == STRIP) 
    return (strip_pattern(pat, pattern_point));
  else if (pat.type == GRADIENT) 
    return (gradient_pattern(pat, pattern_point));
  else if (pat.type == RING)
    return (ring_pattern(pat, pattern_point));
  else if (pat.type == CHECKER)
  {
    if ((int)(floor(point.x) + floor(point.z) + floor(point.y)) % 2 == 0)
      return(pat.a);
    return (pat.b);
  }
  return (tu_create(0, 0, 0, COLOR));
}

