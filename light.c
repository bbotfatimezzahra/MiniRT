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

	printf("light\n");
	if (!rt->scene.light)
	{
		infos = ft_split(str, ' ', &length);
		if (length != 4)
		{
			free_double(infos);
			free(str);
			printf("length %d\n",length);
			terminate("incorrect scene file light\n", rt);
		}
		light = ft_calloc(1, sizeof(t_light));
		if (!light)
		{
			free_double(infos);
			free(str);
			terminate(ERR_MALLOC, rt);
		}
		light->position = tu_parse(infos[1], POINT, rt);
		light->intensity = tu_scale(tu_parse(infos[3], 2, rt),
					check_ratio(ft_atod(infos[2]), 0, rt));
		light->count = 1;
		free_double(infos);
		rt->scene.light = light;
	}
}

void	am_create(char *str, t_mini *rt)
{
	t_color	*ambient;
	char	**infos;
	int	length;

	printf("ambient\n");
	if (!rt->scene.ambient)
	{
		infos = ft_split(str, ' ', &length);
		if (length != 3)
		{
			free_double(infos);
			free(str);
			printf("length %d\n",length);
			terminate("incorrect scene file ambient\n", rt);
		}
		ambient = ft_calloc(1, sizeof(t_tuple));
		if (!ambient)
		{
			free_double(infos);
			free(str);
			terminate(ERR_MALLOC, rt);
		}
		*ambient = tu_scale(tu_parse(infos[2], 2, rt), 
				check_ratio(ft_atod(infos[1]), 0, rt));
		free_double(infos);
		rt->scene.ambient = ambient;
	}
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

t_color	lighting(t_compute cmp, t_light light, bool shade)
{
	t_color	ef_color;
	t_vector	lightv;
	t_color	ambient;
  t_color color;

  color = cmp.obj->material.color;
  if (cmp.obj->material.pattern.enable == true)
    color = pattern_obj(cmp.obj->material.pattern, *cmp.obj, cmp.point);
	ef_color = tu_multiply(color, light.intensity);
	ambient = tu_scale(ef_color, cmp.obj->material.ambient);
  if (shade)
    return (ambient);
	lightv = tu_normalize(tu_subtract(light.position, cmp.point));
	return (tu_add(light_calc(lightv, cmp, ef_color, light), ambient));
}


