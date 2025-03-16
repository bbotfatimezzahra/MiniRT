/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 02:51:49 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 02:53:12 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_color	light_calc(t_vector lightv, t_compute cmp, t_color ef_color, t_light l)
{
	t_color	diffuse;
	t_color	specular;
	double	factor;
	double	re_dot_eye;
	double	li_dot_nor;

	li_dot_nor = tu_dot(lightv, cmp.normalv);
	diffuse = tu_create(0, 0, 0, COLOR);
	specular = tu_create(0, 0, 0, COLOR);
	if (li_dot_nor >= 0)
	{
		diffuse = tu_scale(ef_color, cmp.obj->material.diffuse * li_dot_nor);
		re_dot_eye = tu_dot(ve_reflection(tu_scale(lightv, -1),
					cmp.normalv), cmp.eyev);
		if (re_dot_eye > 0)
		{
			factor = pow(re_dot_eye, cmp.obj->material.shininess);
			specular = tu_scale(l.intensity,
					cmp.obj->material.specular * factor);
		}
	}
	return (tu_add(diffuse, specular));
}

t_color	lighting(t_scene scene, t_compute cmp, t_light light, bool shade)
{
	t_color		ef_color;
	t_vector	lightv;
	t_color		ambient;
	t_color		color;

	color = cmp.obj->material.color;
	if (cmp.obj->material.pattern.enable == true)
		color = pattern_obj(cmp.obj->material.pattern, *cmp.obj, cmp.point);
	ef_color = tu_multiply(color, light.intensity);
	ambient = tu_multiply(ef_color, *scene.ambient);
	if (shade)
		return (ambient);
	lightv = tu_normalize(tu_subtract(light.position, cmp.point));
	return (tu_add(light_calc(lightv, cmp, ef_color, light), ambient));
}

t_color	reflect_color(t_compute cmp, t_scene s, int reflect_recur_checker)
{
	t_ray	reflect_ray;
	t_color	clr;

	reflect_recur_checker++;
	if (cmp.obj->material.reflective < EPS || reflect_recur_checker > 2)
		return (tu_create(0, 0, 0, COLOR));
	reflect_ray.origin = cmp.above_point;
	reflect_ray.direction = cmp.reflectv;
	clr = color_at(s, reflect_ray, reflect_recur_checker);
	return (tu_scale(clr, cmp.xs.object->material.reflective));
}
