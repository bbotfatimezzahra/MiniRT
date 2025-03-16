/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:54:50 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 14:52:52 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	check_vector(t_tuple tuple, int type, t_mini *rt)
{
	double	min;
	double	max;

	if (!type && !tuple.x && !tuple.y && !tuple.z)
		terminate("'NULL' Vector Detected", rt);
	if (type == 0)
	{
		min = -1;
		max = 1;
	}
	else if (type == 2)
	{
		min = 0;
		max = 255;
	}
	else
		return ;
	if (tuple.x < min || tuple.x > max
		|| tuple.y < min || tuple.y > max
		|| tuple.z < min || tuple.z > max)
		terminate("Incorrect Vector Range", rt);
}

t_tuple	tu_parse(char *str, int type, t_mini *rt)
{
	double	coord[3];
	t_tuple	tuple;
	char	*num;

	coord[0] = ft_atod(str, rt, 1);
	num = ft_strchr(str, ',', 1);
	if (!num || !ft_isdigit(num[1]))
		terminate(ERR_SCENE, rt);
	coord[1] = ft_atod(&num[1], rt, 1);
	num = ft_strchr(str, ',', 2);
	if (!num || !ft_isdigit(num[1]))
		terminate(ERR_SCENE, rt);
	coord[2] = ft_atod(&num[1], rt, 1);
	if (ft_strchr(str, ',', 3))
		terminate(ERR_SCENE, rt);
	tuple = tu_create(coord[0], coord[1], coord[2], type);
	check_vector(tuple, type, rt);
	if (type == 2)
		tuple = tu_create(tuple.x / 255, tuple.y / 255,
				tuple.z / 255, 2);
	return (tuple);
}

double	check_ratio(double value, int type, t_mini *rt)
{
	if (type == 2)
		return (value);
	if (value < 0 || (type == 0 && value > 1)
		|| (type == 1 && value > 180)
		|| (type == 3 && value > 200))
		terminate("Incorrect Ratio Value", rt);
	if (type == 1)
		value = value * PI / 180;
	return (value);
}
