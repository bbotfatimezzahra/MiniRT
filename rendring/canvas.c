/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 02:48:58 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/16 02:51:36 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

unsigned long	rgb_to_hex(t_color c)
{
	int	red;
	int	green;
	int	blue;

	red = round(c.x * 255);
	green = round(c.y * 255);
	blue = round(c.z * 255);
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	return ((unsigned long)(red & 0xff) << 16) | ((unsigned long)(green & 0xff) << 8) | (blue & 0xff);
}

void	put_pixel(t_mini *rt, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < (rt->width) && y < (rt->length))
	{
		dst = rt->addr + (y * rt->line_length + x * (rt->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_scaled_pixel(t_mini *rt, t_tuple pt, int color, int scale)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = -scale;
	while (i <= scale)
	{
		j = -scale;
		while (j <= scale)
		{
			x = pt.x + i;
			y = pt.y + j++;
			put_pixel(rt, x, y, color);
		}
		i++;
	}
}

int	key_hook(int keysym, t_mini *rt)
{
	if (keysym == XK_Escape)
		terminate(NULL, rt);
	return (0);
}

int	destroy(t_mini *rt)
{
	terminate(NULL, rt);
	return (0);
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

void	start_display(t_mini *rt)
{
	int		*l_length;
	int		*endian;
	char	*title;

	l_length = &rt->line_length;
	endian = &rt->endian;
	title = "RAYTRACER PROJECT ***FBBOT***";
	rt->con = mlx_init();
	if (!rt->con)
		terminate(ERR_CON, rt);
	rt->win = mlx_new_window(rt->con, rt->width, rt->length, title);
	if (!rt->win)
		terminate(ERR_WIN, rt);
	rt->img = mlx_new_image(rt->con, rt->width, rt->length);
	if (!rt->img)
		terminate(ERR_IMG, rt);
	rt->addr = mlx_get_data_addr(rt->img, &rt->bpp, l_length, endian);
  render_scene(rt);
	printf("\nDONE\n");
	mlx_put_image_to_window(rt->con, rt->win, rt->img, 0, 0);
	mlx_hook(rt->win, 2, 1L << 0, key_hook, rt);
	mlx_hook(rt->win, 17, 1L << 2, destroy, rt);
	mlx_loop(rt->con);
}
	
	
