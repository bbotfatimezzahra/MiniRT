#include "../minirt.h"


static void  cy_util(t_intersections *xs, double c, t_ray ray, t_object *cy);

t_intersections	sp_intersect(t_object *sp, t_ray ray, t_intersections xs)
{
	t_tuple	sp_to_ray;
	double	a;
	double	b;
	double	disc;
  
  xs.count = 0;
	sp_to_ray = tu_subtract(ray.origin, tu_create(0, 0, 0, 1));
	a = tu_dot(ray.direction, ray.direction);
	b = 2 * tu_dot(ray.direction, sp_to_ray);
	disc = b * b - 4 * a * (tu_dot(sp_to_ray, sp_to_ray) - 1);
	if (disc < 0)
		return (xs);
	xs.inter[xs.count].t = (-b - sqrt(disc)) / (2 * a);
	xs.inter[xs.count].object = sp;
	xs.inter[++xs.count].t = (-b + sqrt(disc)) / (2 * a);
	xs.inter[xs.count].object = sp;
	xs.count++;
	return (xs);
}

t_intersections pl_intersect(t_ray r, t_object *pl)
{
  t_intersections xs;

  xs.count = 0;
  if (fabs(r.direction.y) < EPS)
    return (xs);
  xs.inter[0].t = (-r.origin.y / r.direction.y);
  xs.count = 1;
  xs.inter[0].object = pl;
  return (xs);
}

t_intersections	check_cycaps(t_object *cy, t_ray ray, t_intersections xs)
{
	t_cylinder	*obj;
	double	t;
	double	x;
	double	z;

	obj = (t_cylinder *)cy->obj;
	if (!obj->cap || fabs(ray.direction.y) < EPS)
		return (xs);
	t = (obj->miny - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= 1)
	{
		xs.inter[xs.count].object = cy;
		xs.inter[xs.count++].t = t;
	}
	t = (obj->maxy - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= 1)
	{
		xs.inter[xs.count].object = cy;
		xs.inter[xs.count++].t = t;
	}
	return (xs);
}

static void  cy_util(t_intersections *xs, double c, t_ray ray, t_object *cy)
{
  double y;

  y = ray.origin.y + c * ray.direction.y;
	if ( y > -1 && y < 1)
	{
		xs->inter[xs->count].object = cy;
		xs->inter[xs->count++].t = c;
	}
}

t_intersections	cy_intersect(t_object *cy, t_ray ray, t_intersections xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (fabs(a) < EPS)
		return (check_cycaps(cy, ray, xs));
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (check_cycaps(cy, ray, xs));
	c = (-b - sqrt(disc)) / (2 * a);
  cy_util(&xs, c, ray, cy);
  c = (-b + sqrt(disc)) / (2 * a);
  cy_util(&xs, c, ray, cy);
	return (check_cycaps(cy, ray, xs));
}

