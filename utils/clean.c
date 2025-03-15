#include "../minirt.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0 && s)
		(void)!write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (fd >= 0)
	{
		ft_putstr_fd("Error\n", fd);
		ft_putstr_fd(s, fd);
		ft_putstr_fd("\n", fd);
	}
}

void	free_double(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	ptr = NULL;
}

void	free_double_scene(t_mini *rt)
{
	if (rt->scene.light)
	{
		while (--rt->scene.numlight >= 0)
		{
			if (rt->scene.light[rt->scene.numlight])
				free(rt->scene.light[rt->scene.numlight]);
		}
		free(rt->scene.light);
	}
	if (rt->scene.objs)
	{
		while (--rt->scene.count >= 0)
		{
			if (rt->scene.objs[rt->scene.count])
			{
				if (rt->scene.objs[rt->scene.count]->obj)
					free(rt->scene.objs[rt->scene.count]->obj);
				free(rt->scene.objs[rt->scene.count]);
			}
		}
		free(rt->scene.objs);
	}
}

void	terminate(char *error, t_mini *rt)
{
	free_double_scene(rt);
	if (rt->scene.camera)
		free(rt->scene.camera);
	if (rt->scene.ambient)
		free(rt->scene.ambient);
	if (rt->parse_str)
		free(rt->parse_str);
	if (rt->parse_elems)
		free_double(rt->parse_elems);
	if (rt->parse_infos)
		free_double(rt->parse_infos);
	if (rt->img)
		mlx_destroy_image(rt->con, rt->img);
	if (rt->win)
		mlx_destroy_window(rt->con, rt->win);
	if (rt->con)
	{
		mlx_destroy_display(rt->con);
		free(rt->con);
	}
	if (error)
		ft_putendl_fd(error, 2);
	exit(0);
}
