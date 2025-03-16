#include "../minirt.h"

t_intersections	check_cycaps(t_object *cy, t_ray ray, t_intersections xs)
{
	t_cylinder	*obj;
	double		t;
	double		x;
	double		z;

	obj = (t_cylinder *)cy->obj;
	if (!obj->cap || fabs(ray.direction.y) < EPS)
		return (xs);
	t = (obj->miny - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z) <= 1)
	{
		xs.inter[xs.count].object = cy;
		xs.inter[xs.count++].t = t;
	}
	t = (obj->maxy - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z) <= 1)
	{
		xs.inter[xs.count].object = cy;
		xs.inter[xs.count++].t = t;
	}
	return (xs);
}

void	c_util(t_intersections *xs, double c, t_ray ray, t_object *obj)
{
	double	y;

	y = ray.origin.y + c * ray.direction.y;
	if (y > -1 && y < 1)
	{
		xs->inter[xs->count].object = obj;
		xs->inter[xs->count++].t = c;
	}
}

t_intersections	check_cocaps(t_object *co, t_ray ray, t_intersections xs)
{
	t_cone	*obj;
	double	t;
	double	x;
	double	z;

	obj = (t_cone *)co->obj;
	if (!obj->cap || fabs(ray.direction.y) < EPS)
		return (xs);
	t = (obj->miny - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z) <= fabs(ray.origin.y + t * ray.direction.y))
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = t;
	}
	t = (obj->maxy - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z) <= fabs(ray.origin.y + t * ray.direction.y))
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = t;
	}
	return (xs);
}

void	calc_factors(t_ray ray, double *a, double *b, double *c)
{
	double	aidx;
	double	aidy;
	double	aidz;

	aidx = pow(ray.direction.x, 2);
	aidy = pow(ray.direction.y, 2);
	aidz = pow(ray.direction.z, 2);
	*a = aidx - aidy + aidz;
	aidx = 2 * ray.origin.x * ray.direction.x;
	aidy = 2 * ray.origin.y * ray.direction.y;
	aidz = 2 * ray.origin.z * ray.direction.z;
	*b = aidx - aidy + aidz;
	*c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2) + pow(ray.origin.z, 2);
}
