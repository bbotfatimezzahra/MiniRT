#include "minirt.h"

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
}
/*
void	free_maps(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map.rows)
	{
		if (fdf->map.points[i])
			free(fdf->map.points[i]);
		if (fdf->map.tmps[i])
			free(fdf->map.tmps[i]);
		i++;
	}
	if (fdf->map.points)
		free(fdf->map.points);
	if (fdf->map.tmps)
		free(fdf->map.tmps);
}
*/
void	terminate(char *error, t_mini *rt)
{
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
		ft_putendl_fd(error, 1);
	else
		perror(NULL);
	exit(0);
}
