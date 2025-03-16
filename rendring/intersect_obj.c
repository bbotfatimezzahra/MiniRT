/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:44:29 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 15:48:59 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

t_intersections	pl_intersect(t_ray r, t_object *pl)
{
	t_intersections	xs;

	xs.count = 0;
	if (fabs(r.direction.y) < EPS)
		return (xs);
	xs.inter[0].t = (-r.origin.y / r.direction.y);
	xs.count = 1;
	xs.inter[0].object = pl;
	return (xs);
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
	c_util(&xs, c, ray, cy);
	c = (-b + sqrt(disc)) / (2 * a);
	c_util(&xs, c, ray, cy);
	return (check_cycaps(cy, ray, xs));
}

t_intersections	co_intersect(t_object *co, t_ray ray, t_intersections xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	calc_factors(ray, &a, &b, &c);
	if (fabs(a) < EPS && fabs(b) < EPS)
		return (xs);
	else if (fabs(a) < EPS)
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = -c / (2 * b);
		return (check_cocaps(co, ray, xs));
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (check_cocaps(co, ray, xs));
	c = (-b - sqrt(disc)) / (2 * a);
	c_util(&xs, c, ray, co);
	c = (-b + sqrt(disc)) / (2 * a);
	c_util(&xs, c, ray, co);
	return (check_cocaps(co, ray, xs));
}
