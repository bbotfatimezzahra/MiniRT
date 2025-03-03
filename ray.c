#include "minirt.h"

t_ray	ra_create(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ra_position(t_ray ray, double t)
{
	return (tu_add(ray.origin, tu_scale(ray.direction, t)));
}

t_ray	ra_transform(t_ray ray, t_matrix matrix)
{
	t_ray	new;

	new.origin = ma_tu_multiply(matrix, ray.origin);
	new.direction = ma_tu_multiply(matrix, ray.direction);
	return (new);
}
