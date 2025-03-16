/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:33:21 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 15:33:26 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

long	rgb_to_hex(t_color c)
{
	int	red;
	int	green;
	int	blue;

	red = round(c.x * 255);
	green = round(c.y * 255);
	blue = round(c.z * 255);
	if (red < 0)
		red = 0;
	if (green < 0)
		green = 0;
	if (blue < 0)
		blue = 0;
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return ((long)(red << 16) | ((long)(green << 8)) | (blue & 0xff));
}

float	limit_value(float color)
{
	float	value;

	value = color * 256;
	if (value < 0)
		return (0);
	else if (value > 255)
		return (255);
	return (value);
}
