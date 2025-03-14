/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:02:54 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 19:24:59 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	li_create(char *str, t_mini *rt)
{
	t_light	*light;
	char	**infos;
	int	length;

	if (!rt->scene.light)
	{
		rt->parse_infos = ft_split(str, ' ', &length);
		infos = rt->parse_infos;
		if (length != 4 || ft_strncmp(infos[0], "L", 2))
			terminate("incorrect scene file light\n", rt);
		light = ft_calloc(1, sizeof(t_light));
		if (!light)
			terminate(ERR_MALLOC, rt);
		light->position = tu_parse(infos[1], POINT, rt);
		light->intensity = tu_scale(tu_parse(infos[3], 2, rt),
					check_ratio(ft_atod(infos[2], rt), 0, rt));
		light->count = 1;
		rt->scene.light = light;
		free_double(rt->parse_infos);
		rt->parse_infos = NULL;
	}
	printf("light\n");
}

void	am_create(char *str, t_mini *rt)
{
	t_color	*ambient;
	char	**infos;
	int	length;

	if (!rt->scene.ambient)
	{
		rt->parse_infos = ft_split(str, ' ', &length);
		infos = rt->parse_infos;
		if (length != 3|| ft_strncmp(infos[0], "A", 2))
			terminate("incorrect scene file ambient\n", rt);
		ambient = ft_calloc(1, sizeof(t_tuple));
		if (!ambient)
			terminate(ERR_MALLOC, rt);
		*ambient = tu_scale(tu_parse(infos[2], 2, rt), 
				check_ratio(ft_atod(infos[1], rt), 0, rt));
		rt->scene.ambient = ambient;
		free_double(rt->parse_infos);
		rt->parse_infos = NULL;
	}
	printf("ambient\n");
}

t_color light_calc(t_vector lightv, t_compute cmp, t_color ef_color, t_light l)
{
	t_color	diffuse;
	t_color	specular;
	double	factor;
	double	re_dot_eye;
	double	li_dot_nor;

	li_dot_nor = tu_dot(lightv, cmp.normalv);
	if (li_dot_nor < 0)
	{
		diffuse = tu_create(0, 0, 0, COLOR);
		specular = tu_create(0, 0, 0, COLOR);
	}
	else
	{
		diffuse = tu_scale(ef_color, cmp.obj->material.diffuse * li_dot_nor);
		re_dot_eye = tu_dot(ve_reflection(tu_scale(lightv, -1), cmp.normalv), cmp.eyev);
		if (re_dot_eye <= 0)
			specular = tu_create(0, 0, 0, COLOR);
		else
		{
			factor = pow(re_dot_eye, cmp.obj->material.shininess);
			specular = tu_scale(l.intensity, cmp.obj->material.specular * factor);
		}
	}
	return (tu_add(diffuse, specular));
}

t_color	lighting(t_scene scene, t_compute cmp, t_light light, bool shade)
{
	t_color	ef_color;
	t_vector	lightv;
	t_color	ambient;
  t_color color;

  color = cmp.obj->material.color;
  if (cmp.obj->material.pattern.enable == true)
    color = pattern_obj(cmp.obj->material.pattern, *cmp.obj, cmp.point);
	ef_color = tu_multiply(color, light.intensity);
	ambient = tu_multiply(ef_color, *scene.ambient);
  if (shade)
    return (ambient);
  /*print_tuple(ambient);*/
	lightv = tu_normalize(tu_subtract(light.position, cmp.point));
	return (tu_add(light_calc(lightv, cmp, ef_color, light), ambient));
}


