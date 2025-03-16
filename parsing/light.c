/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:02:54 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 15:24:05 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	li_create(char *str, t_mini *rt)
{
	t_light	*light;
	char	**infos;
	int		length;

	rt->parse_infos = ft_split(str, ' ', &length);
	if (!rt->parse_infos)
		terminate(ERR_MALLOC, rt);
	infos = rt->parse_infos;
	if (length != 4 || ft_strncmp(infos[0], "L", 2))
		terminate("Incorrect Light Line", rt);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		terminate(ERR_MALLOC, rt);
	rt->scene.light[rt->scene.numlight++] = light;
	light->position = tu_parse(infos[1], POINT, rt);
	light->intensity = tu_scale(tu_parse(infos[3], 2, rt),
			check_ratio(ft_atod(infos[2], rt, 0), 0, rt));
	free_double(&rt->parse_infos);
	printf("light\n");
}

void	am_create(char *str, t_mini *rt)
{
	t_color	*ambient;
	char	**infos;
	int		length;

	if (!rt->scene.ambient)
	{
		rt->parse_infos = ft_split(str, ' ', &length);
		if (!rt->parse_infos)
			terminate(ERR_MALLOC, rt);
		infos = rt->parse_infos;
		if (length != 3 || ft_strncmp(infos[0], "A", 2))
			terminate("Incorrect Ambient Line", rt);
		ambient = ft_calloc(1, sizeof(t_tuple));
		if (!ambient)
			terminate(ERR_MALLOC, rt);
		rt->scene.ambient = ambient;
		*ambient = tu_scale(tu_parse(infos[2], 2, rt),
				check_ratio(ft_atod(infos[1], rt, 0), 0, rt));
		free_double(&rt->parse_infos);
	}
	else
		terminate("Only One Ambient Needed", rt);
	printf("ambient\n");
}
