/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:00:55 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 15:55:54 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ca_create(char *str, t_mini *rt)
{
	t_camera	*camera;
	char	**infos;
	int	length;

	printf("Camera\n");
	if (!rt->scene.camera)
	{
		rt->parse_infos = ft_split(str, ' ', &length);
		infos = rt->parse_infos;
		if (length != 4)
			terminate("incorrect scene file camera\n", rt);
		camera = ft_calloc(1, sizeof(t_camera));
		if (!camera)
			terminate(ERR_MALLOC, rt);
		*camera = set_camera(DIS_WIDTH, DIS_LENGTH,
				check_ratio(ft_atod(infos[3]), 1, rt));
		camera->transform = view_transform(tu_parse(infos[1], 
				1, rt), tu_parse(infos[2], 0, rt));
		print_matrix(camera->transform);
		rt->scene.camera = camera;
		free_double(rt->parse_infos);
		rt->parse_infos = NULL;
	}
}
