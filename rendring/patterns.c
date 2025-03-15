#include "../minirt.h"

t_pattern new_pattern(void)
{
	t_pattern new;

  new.enable = false;
  new.type = NONE;
  new.a = tu_create(1, 1, 1, 2);
  new.b = tu_create(0, 0, 0, 2);
  new.transform = ma_identity(4);
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
  t_point obj_point;
  t_point	pat_point;

  obj_point = ma_tu_multiply(obj.transform, point);
  pat_point = ma_tu_multiply(pat.transform, obj_point);
  if (pat.type == STRIPE) 
    return (strip_pattern(pat, pat_point));
  else if (pat.type == GRADIENT) 
    return (gradient_pattern(pat, pat_point));
  else if (pat.type == RING)
    return (ring_pattern(pat, pat_point));
  else if (pat.type == CHECKER)
  {
    if ((int)(floor(point.x) + floor(point.z) + floor(point.y)) % 2 == 0)
      return(pat.a);
    return (pat.b);
  }
  return (tu_create(0, 0, 0, COLOR));
}

