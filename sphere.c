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
	obj->type = SPHERE;
	obj->obj = sphere;
	return (obj);
}

void	sp_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;
	double	a;

	rt->parse_infos = ft_split(str, ' ', &length);
	infos = rt->parse_infos;
	if (length < 4 || ft_strncmp(infos[0], "sp", 3))
		terminate("Incorrect scene file\n", rt);
	obj = sp_create(rt);
	rt->scene.objs[rt->scene.count++] = obj;
	a = ft_atod(infos[2], rt, 0) / 2;
	obj->transform = ma_scale(tu_create(a, a, a, 1));
	obj->transform = ma_multiply(ma_translate(tu_parse(infos[1], 1, rt)),
                              obj->transform);
	obj->material = m_create(tu_parse(infos[3], 2, rt));
	if (length > 4)
		obj->material = m_parse(rt, obj->material, 4);
	obj->id = rt->scene.count;
	free_double(rt->parse_infos);
	rt->parse_infos = NULL;
	printf("Sphere\n");
}
