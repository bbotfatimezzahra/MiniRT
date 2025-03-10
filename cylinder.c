#include "minirt.h"

t_object	*cy_create(t_mini *rt)
{
	t_object	*obj;
	t_cylinder	*cy;

	printf("Cyllinder\n");
	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		terminate(ERR_MALLOC, rt);
	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		terminate(ERR_MALLOC, rt);
	cy->radius = 1;
	cy->origin = tu_create(0, 0, 0, POINT);
	cy->miny = -1;
	cy->maxy = 1;
	cy->cap = 0;
	obj->type = CYLINDER;
	obj->material = m_create(tu_create(1,1,1,2));
	obj->transform = ma_identity(4);
	obj->obj = cy;
	return(obj);
}

void	cy_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;
	double	a;

	printf("Cylinder\n");
	rt->parse_infos = ft_split(str, ' ', &length);
	infos = rt->parse_infos;
	if (length != 6)
		terminate("Incorrect scene file\n", rt);
	obj = cy_create(rt);
	a = ft_atod(infos[3]) / 2;
	obj->transform = ma_translate(tu_parse(infos[1], 1, rt));
	obj->transform = ma_multiply(obj->transform,
			ma_scale(tu_create(a, ft_atod(infos[4]), a, 1)));
//	obj->transform = ma_multiply(obj->transform,
//			ma_rodrigues(tu_parse(infos[2], 0)));
	obj->material = m_create(tu_parse(infos[5], 2, rt));
	obj->id = rt->scene.count;
	rt->scene.objs[rt->scene.count] = obj;
	rt->scene.count++;
	free_double(rt->parse_infos);
	rt->parse_infos = NULL;
}
