/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:57:39 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 12:57:40 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	tu_add(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res.x = t1.x + t2.x;
	res.y = t1.y + t2.y;
	res.z = t1.z + t2.z;
	res.w = t1.w + t2.w;
	if (t1.w == 2 && t2.w == 2)
		res.w = 2;
	return (res);
}

t_tuple	tu_subtract(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res.x = t1.x - t2.x;
	res.y = t1.y - t2.y;
	res.z = t1.z - t2.z;
	res.w = t1.w - t2.w;
	if (t1.w == 2 && t2.w == 2)
		res.w = 2;
	return (res);
}

double	tu_dot(t_tuple t1, t_tuple t2)
{
	double	res;

	res = t1.x * t2.x;
	res += t1.y * t2.y;
	res += t1.z * t2.z;
	res += t1.w * t2.w;
	return (res);
}

t_tuple	tu_cross(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res.x = t1.y * t2.z - t1.z * t2.y;
	res.y = t1.z * t2.x - t1.x * t2.z;
	res.z = t1.x * t2.y - t1.y * t2.x;
	res.w = 0;
	return (res);
}

t_tuple	tu_multiply(t_tuple t1, t_tuple t2)
{
	t_tuple	res;

	res.x = t1.x * t2.x;
	res.y = t1.y * t2.y;
	res.z = t1.z * t2.z;
	res.w = t1.w * t2.w;
	if (t1.w == 2 && t2.w == 2)
		res.w = 2;
	return (res);
}
