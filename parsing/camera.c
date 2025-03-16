/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:00:55 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 15:24:05 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static	t_vector	find_non_parallel_ve(t_vector v);

t_matrix	view_transform(t_point from, t_vector orient)
{
	t_vector	forward;
	t_vector	left;
	t_vector	normalize_up;
	t_vector	real_up;
	t_matrix	orient_mat;

	forward = tu_normalize(orient);
	normalize_up = tu_normalize(find_non_parallel_ve(orient));
	left = tu_cross(forward, normalize_up);
	left = tu_normalize(left);
	real_up = tu_cross(left, forward);
	orient_mat = ma_tu_fill(left, real_up, tu_scale(forward, -1),
			tu_create(0, 0, 0, POINT));
	return (ma_multiply(orient_mat,
			ma_translate(tu_create(-from.x, -from.y, -from.z, 0))));
}

t_camera	set_camera(double hsize, double vsize, double fov)
{
	double		half_view;
	float		aspect;
	t_camera	c;

	c.horizontal_size = hsize;
	c.vertical_size = vsize;
	c.transform = ma_identity(4);
	half_view = tan(fov / 2);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_hight = c.half_width / aspect;
	}
	else
	{
		c.half_hight = half_view;
		c.half_width = aspect * c.half_hight;
	}
	c.pixel_size = (2 * c.half_width) / hsize;
	return (c);
}

static	t_vector	find_non_parallel_ve(t_vector v)
{
	if (tu_magnitude(tu_cross(v, tu_create(0, 1, 0, VECTOR))) != 0)
		return (tu_create(0, 1, 0, VECTOR));
	if (tu_magnitude(tu_cross(v, tu_create(1, 0, 0, VECTOR))) != 0)
		return (tu_create(0, 0, 1, VECTOR));
	return (tu_create(1, 0, 0, VECTOR));
}

void	ca_create(char *str, t_mini *rt)
{
	t_camera	*camera;
	char		**infos;
	int			length;

	printf("Camera\n");
	if (!rt->scene.camera)
	{
		rt->parse_infos = ft_split(str, ' ', &length);
		if (!rt->parse_infos)
			terminate(ERR_MALLOC, rt);
		infos = rt->parse_infos;
		if (length != 4 || ft_strncmp(infos[0], "C", 2))
			terminate("Incorrect Camera Line", rt);
		camera = ft_calloc(1, sizeof(t_camera));
		if (!camera)
			terminate(ERR_MALLOC, rt);
		rt->scene.camera = camera;
		*camera = set_camera(DIS_WIDTH, DIS_LENGTH,
				check_ratio(ft_atod(infos[3], rt, 0), 1, rt));
		camera->transform = view_transform(tu_parse(infos[1],
					1, rt), tu_parse(infos[2], 0, rt));
		free_double(&rt->parse_infos);
	}
	else
		terminate("Only One Camera Needed", rt);
}
