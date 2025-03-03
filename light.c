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
	if (!str)
	{
		light.count = 0;
		light.type = 1;
		light.position = tu_create(-10, 10, -10, 1);
		light.intensity = tu_create(1,1,1,2);
	}
	else if (rt->scene.light.count == 1)
		return ;
	else
	{
		infos = ft_split(str, ' ', &length);
		if (length != 4)
		{
			free_double(infos);
			free(str);
			terminate("Incorrect scene file\n", rt);
		}
		light.type = 1;
		light.position = tu_parse(infos[1], POINT);
		light.intensity = tu_scale(tu_parse(infos[3], 2), ft_atod(infos[2]));
		light.count = rt->scene.light.count + 1;
		free_double(infos);
	}
	rt->scene.light = light;
}

t_color	lighting(t_material material, t_light light, t_point point, t_vector eyev, t_vector normalv)
{
	t_color	ef_color;
	t_vector	lightv;
	t_vector	reflectv;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	double	li_dot_nor;
	double	re_dot_eye;
	double	factor;

	print_tuple(material.color);
	print_tuple(light.intensity);
	ef_color = tu_multiply(material.color, light.intensity);
//	printf("ef_color\n");
	//print_tuple(ef_color);
	lightv = tu_normalize(tu_subtract(light.position, point));
	//printf("lightv\n");
	//print_tuple(lightv);
	ambient = tu_scale(ef_color, material.ambient);
	//printf("ambient\n");
	//print_tuple(ambient);
	li_dot_nor = tu_dot(lightv, normalv);
	//printf("li_dot_nor = %f\n",li_dot_nor);
	if (li_dot_nor < 0)
	{
		diffuse = tu_create(0, 0, 0, 2);
		//printf("diffuse\n");
		//print_tuple(diffuse);
		specular = tu_create(0, 0, 0, 2);
		//printf("specular\n");
		//print_tuple(specular);
	}
	else
	{
		diffuse = tu_scale(ef_color, material.diffuse * li_dot_nor);
		//printf("diffuse\n");
		//print_tuple(diffuse);
		reflectv = ve_reflection(tu_scale(lightv, -1), normalv);
		//printf("reflectv\n");
		//print_tuple(reflectv);
		re_dot_eye = tu_dot(reflectv, eyev);
		//printf("re_dot_eye = %f\n",re_dot_eye);
		if (re_dot_eye <= 0)
		{
			specular = tu_create(0, 0, 0, 2);
			//printf("specular\n");
			//print_tuple(specular);
		}
		else
		{
			factor = pow(re_dot_eye, material.shininess);
			//printf("factor = %f\n",factor);
			specular = tu_scale(light.intensity, material.specular * factor);
			//printf("specular\n");
		//	print_tuple(specular);
		}
	}
	return (tu_add(tu_add(ambient, diffuse), specular));
}
