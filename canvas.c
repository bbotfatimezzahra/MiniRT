#include "minirt.h"

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
		terminate(" ", rt);
	return (0);
}

int	destroy(t_mini *rt)
{
	terminate(" ", rt);
	return (0);
}

void	draw_background(t_mini *rt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < rt->width)
	{
		j = 0;
		while (j < rt->length)
			put_pixel(rt, i, j++, BLACK);
		i++;
	}
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

int	convert_color(t_color rgb)
{
	int	color;

	color = limit_value(rgb.x);
	color = (color << 8) +  limit_value(rgb.y);
	color = (color << 8) +  limit_value(rgb.z);
	printf("%d\n",color);
	return (color);
}
void	fill_image(t_mini *rt)
{
	(void)rt;
/*
	t_cylinder	cy;
	t_ray	ray;
	t_intersect	hit;
	int	i;
	int	j;
	t_tuple dir;
	t_tuple	origin;
	float	half_wall;
	float	pixel_size;
	float	wall_size;
	float	world_x;
	float	world_y;
	t_light	light;
	t_vector	normal;
	t_vector	cam;
	t_point	point;
	t_color	color;
	t_intersections hi;

	origin = tu_create(0, 0, -5, POINT);
	cy = cy_create();
	cy.miny = 0;
	cy.maxy = 200;
	cy.material.color = tu_create(1, 0.2, 1, 2);
	light = li_create(tu_create(-10, 10, -10, 1), tu_create(1,1,1,2));
	wall_size = 7;
	pixel_size = wall_size / DIS_WIDTH;
	half_wall = wall_size / 2;
	i = 0;
	while (i < DIS_WIDTH)
	{
		j = 0;
		world_x = -half_wall + pixel_size * i;
		while (j <= DIS_LENGTH)
		{
			world_y = half_wall - pixel_size * j;
			dir = tu_create(world_x, world_y, wall_size, POINT);
			ray = ra_create(origin, tu_normalize(tu_subtract(dir, origin)));
			hi.count = 0;
			hit = hits(cy_intersect(cy, ray, hi));
			if (hit.t >= 0)
			{
				point = ra_position(ray,hit.t);
				normal = ve_cy_normal(cy, point);
				cam = ve_camera(ray);
				color = lighting(cy.material, light, point, cam, normal);
				print_tuple(color);
				put_pixel(rt, i, j, convert_color(color));
			}
			j++;
		}
		i++;
	}
*/
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
	draw_background(rt);
	fill_image(rt);
	mlx_put_image_to_window(rt->con, rt->win, rt->img, 0, 0);
	mlx_hook(rt->win, 2, 1L << 0, key_hook, rt);
	mlx_hook(rt->win, 17, 1L << 2, destroy, rt);
	mlx_loop(rt->con);
}
	
	
