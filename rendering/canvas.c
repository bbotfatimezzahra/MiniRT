/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snidbell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 02:48:58 by snidbell          #+#    #+#             */
/*   Updated: 2025/03/17 15:14:54 by snidbell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

void	start_display(t_mini *rt)
{
	int		*l_length;
	int		*endian;
	char	*title;

	l_length = &rt->line_length;
	endian = &rt->endian;
	title = "DJAMEEL";
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
