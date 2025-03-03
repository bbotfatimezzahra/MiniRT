#include "minirt.h"

t_intersections	sp_intersect(t_sphere sp, t_ray ray, t_intersections inter)
{
	t_tuple	sp_to_ray;
	double	a;
	double	b;
	double	disc;

	ray = ra_transform(ray, ma_invert(sp.transform));
	sp_to_ray = tu_subtract(ray.origin, sp.origin);
	a = tu_dot(ray.direction, ray.direction);
	b = 2 * tu_dot(ray.direction, sp_to_ray);
	disc = b * b - 4 * a * (tu_dot(sp_to_ray, sp_to_ray) - 1);
	if (disc < 0)
		return (inter);
	inter.x[inter.count].t = (-b - sqrt(disc)) / (2 * a);
	inter.x[inter.count].object = sp.id;
	inter.x[++inter.count].t = (-b + sqrt(disc)) / (2 * a);
	inter.x[inter.count].object = sp.id;
	inter.count++;
	return (inter);
}

t_intersections	check_caps(t_cylinder cy, t_ray ray, t_intersections inter)
{
	double	t;
	double	x;
	double	z;

	if (!cy.cap || fabs(ray.direction.y) < EPS)
		return (inter);
	t = (cy.miny - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= 1)
	{
		inter.x[inter.count].object = cy.id;
		inter.x[inter.count++].t = t;
		printf("first cap\n");
	}
	t = (cy.maxy - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= 1)
	{
		inter.x[inter.count].object = cy.id;
		inter.x[inter.count++].t = t;
		printf("second cap\n");
	}
	return (inter);
}

t_intersections	cy_intersect(t_cylinder cy, t_ray ray, t_intersections inter)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	y;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	printf("a = %f\n", a);
	if (fabs(a) < EPS)
		return (check_caps(cy, ray, inter));
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - 1;
	disc = b * b - 4 * a * c;
	printf("disc = %f\n", disc);
	if (disc < 0)
		return (check_caps(cy, ray, inter));
	c = (-b - sqrt(disc)) / (2 * a);
	y = ray.origin.y + c * ray.direction.y;
	if ( y > cy.miny && y < cy.maxy)
	{
		inter.x[inter.count].object = cy.id;
		inter.x[inter.count++].t = c;
		printf("first\n");
	}
	c = (-b + sqrt(disc)) / (2 * a);
	y = ray.origin.y + c * ray.direction.y;
	if ( y > cy.miny && y < cy.maxy)
	{
		inter.x[inter.count].object = cy.id;
		inter.x[inter.count++].t = c;
		printf("second\n");
	}
	return (check_caps(cy, ray, inter));
}

t_intersect	hits(t_intersections inter)
{
	int	i;
	t_intersect	hit;

	hit.t = -1;
	if (!inter.count)
		return (hit);
	i = inter.count - 1;
	while (i >= 0 && inter.x[i].t >= 0)
	{
		if (hit.t < 0 || hit.t >= inter.x[i].t)
			hit = inter.x[i];
		i--;
	}
	return (hit);
}
