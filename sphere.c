#include "minirt.h"

t_object	*sp_create(t_mini *rt)
{
	t_object	*obj;
	t_sphere	*sphere;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		terminate(ERR_MALLOC, rt);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		terminate(ERR_MALLOC, rt);
	sphere->origin = tu_create(0, 0, 0, POINT);
	sphere->radius = 1;
	obj->material = m_create(tu_create(1, 1, 1, 2));
	obj->transform = ma_identity(4);
	obj->type = SP;
	obj->obj = sphere;
	return (obj);
}

void	sp_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;
	double	a;

	printf("Sphere\n");
	infos = ft_split(str, ' ', &length);
	if (length != 4)
	{
		free_double(infos);
		free(str);
		terminate("Incorrect scene file\n", rt);
	}
	obj = sp_create(rt);
	a = ft_atod(infos[2]) / 2;
	obj->transform = ma_translate(tu_parse(infos[1], 1, rt));
	obj->transform = ma_multiply(obj->transform,
			ma_scale(tu_create(a, a, a, 1)));
	obj->material = m_create(tu_parse(infos[3], 2, rt));
	obj->id = rt->scene.count;
	free_double(infos);
	rt->scene.objs[rt->scene.count] = obj;
	rt->scene.count++;
}
/*
t_sphere	sp_transform(t_sphere sp, t_matrix matrix)
{
	sp.transform = ma_multiply(matrix, sp.transform);
	return (sp);
}*/
