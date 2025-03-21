/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:49:13 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 16:18:17 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_compute	prepare(t_intersections xs, t_ray ray)
{
	t_compute	new;

	new.xs = hit(xs);
	new.obj = new.xs.object;
	new.point = ray_position(ray, hit(xs).t);
	new.eyev = tu_scale(ray.direction, -1);
	new.normalv = ve_normal_at(new.xs.object, new.point);
	new.inside = false;
	if (tu_dot(new.normalv, new.eyev) < 0)
	{
		new.normalv = tu_scale(new.normalv, -1);
		new.inside = true;
	}
	new.reflectv = tu_normalize(ve_reflection(ray.direction, new.normalv));
	new.above_point = tu_add(new.point, tu_scale(new.normalv, EPS));
	new.under_point = tu_subtract(new.point, tu_scale(new.normalv, EPS));
	return (new);
}

t_color	color_at(t_scene s, t_ray r, int reflect_recur_checker)
{
	t_intersections	xs_world;
	t_compute		cmp;

	xs_world = intersect_world(s, r);
	if (xs_world.count <= 0 || hit(xs_world).t < EPS)
		return (tu_create(0, 0, 0, COLOR));
	cmp = prepare(xs_world, r);
	return (shade_hit(s, cmp, reflect_recur_checker));
}

t_color	shade_hit(t_scene s, t_compute cmp, int reflect_recur_checker)
{
	bool	shade;
	t_color	initial_color;
	t_color	reflected_color;
	int		i;

	i = 0;
	initial_color = tu_create(0, 0, 0, COLOR);
	while (i < s.numlight)
	{
		shade = false;
		shade = pixel_is_shadow(s, cmp.above_point, i);
		initial_color = tu_add(lighting(s, cmp, *s.light[i], shade),
				initial_color);
		i++;
	}
	reflected_color = reflect_color(cmp, s, reflect_recur_checker);
	return (tu_add(reflected_color, initial_color));
}

bool	pixel_is_shadow(t_scene s, t_tuple above_point, int i)
{
	double			distance_point_light;
	t_intersections	xs;
	t_ray			r;

	r.direction = tu_subtract(s.light[i]->position, above_point);
	distance_point_light = tu_magnitude(r.direction);
	r.direction = tu_normalize(r.direction);
	r.origin = above_point;
	xs = intersect_world(s, r);
	if (hit(xs).t > EPS && hit(xs).t - EPS <= distance_point_light)
		return (true);
	return (false);
}
