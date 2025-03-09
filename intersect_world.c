#include "minirt.h"


/*static void bubble_sort(t_intersections *xs);*/

t_intersections  intersect_each(t_ray r, t_object *obj)
{
  t_ray transformed_ray;
  t_intersections xs;
  
  xs.count = 0;
  transformed_ray = ray_transform(r, ma_invert(obj->transform));// here we convert the ray to object space
  if (obj->type == SPHERE)
    return (sp_intersect(obj, transformed_ray, xs));
  else if(obj->type == PLANE)
    return(pl_intersect(transformed_ray, obj));
  return (xs);
}

t_intersect	hit(t_intersections xs)
{
	int	i;
	t_intersect	hit;

	hit.t = -1;
	if (!xs.count)
		return (hit);
	i = xs.count - 1;
	while (i >= 0 && xs.inter[i].t >= 0)
	{
		if (hit.t < 0 || (hit.t > xs.inter[i].t && xs.inter[i].t > EPS))
			hit = xs.inter[i];
		i--;
	}
	return (hit);
}

/*static void bubble_sort(t_intersections *xs)*/
/*{*/
/*  int i;*/
/*  int j;*/
/*  bool swapped;*/
/*  t_intersect tmp;*/
/**/
/*  i = 0;*/
/*  while(i < xs->count)*/
/*  {*/
/*    j = 0;*/
/*    swapped = false;*/
/*    while(j < xs->count - i)*/
/*    {*/
/*      if (xs->inter[j + 1].t < xs->inter[j].t)      */
/*      {*/
/*        swapped = true;*/
/*        tmp = xs->inter[j];*/
/*        xs->inter[j] = xs->inter[j + 1];  */
/*        xs->inter[j + 1] = tmp; */
/*      }*/
/*      j++;*/
/*    }*/
/*    if (swapped == false)*/
/*      break;*/
/*    i++;*/
/*  }*/
/*}*/

/*t_intersections  intersect_world(t_world w, t_ray r)*/
/*{*/
/*  t_intersections world_xs;*/
/*  t_intersections obj_xs; */
/*  size_t i;*/
/*  int j;*/
/*  int k;*/
/**/
/*  i = 0;*/
/*  k = 0;*/
/*  world_xs.count = 0;*/
/*  while (i < w.number_of_object)*/
/*  {*/
/*    obj_xs = intersect_each(r, &w.obj[i]);*/
/*    if (obj_xs.count != 0)*/
/*    {*/
/*      j = 0;*/
/*      world_xs.count += obj_xs.count;*/
/*      while (j < obj_xs.count && world_xs.count < 1024)*/
/*      {*/
/*        world_xs.inter[k] = obj_xs.inter[j];*/
/*        k++;*/
/*        j++;*/
/*      }*/
/*    }*/
/*    i++;*/
/*  }*/
/*  bubble_sort(world_xs);*/
/*  return (world_xs);*/
/*}*/

t_intersections  intersect_world(t_scene s, t_ray r)
{
  t_intersections world_xs;
  t_intersections obj_xs; 
  int i;
  int j;

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
  /*bubble_sort(&world_xs);*/
  return (world_xs);
}

