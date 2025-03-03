#include "minirt.h"

void	sp_create(char *str, t_mini *rt)
{
	t_sphere	sphere;
	char	**infos;
	int	length;

	printf("Sphere\n");
	if (!str)
	{
		sphere.id = 0;
		sphere.count = 0;
		sphere.origin = tu_create(0, 0, 0, POINT);
		sphere.radius = 1;
		sphere.material = m_create(tu_create(1,1,1,2));
		sphere.transform = ma_identity(4);
	}
	else
	{
		infos = ft_split(str, ' ', &length);
		if (length != 4)
		{
			free_double(infos);
			free(str);
			terminate("Incorrect scene file\n", rt);
		}
		sphere.id = rt.scene.sp[0].count++;
		sphere.origin = tu_parse(infos[1], POINT);
		sphere.radius = ft_atod(infos[2]) / 2;
		sphere.material = m_create(tu_parse(infos[3], 2));
		sphere.transform = ma_identity(4);
		free_double(infos);
	}
	rt.scene.sp[sphere.id] = sphere;
	return (rt);
}

t_sphere	sp_transform(t_sphere sp, t_matrix matrix)
{
	sp.transform = ma_multiply(matrix, sp.transform);
	return (sp);
}
