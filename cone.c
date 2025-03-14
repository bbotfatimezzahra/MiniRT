#include "minirt.h"

t_object	*co_create(t_mini *rt)
{
	t_object	*obj;
	t_cone	*co;

	obj = ft_calloc(1, sizeof(t_object));
	if (!obj)
		terminate(ERR_MALLOC, rt);
	co = ft_calloc(1, sizeof(t_cone));
	if (!co)
		terminate(ERR_MALLOC, rt);
	co->radius = 1;
	co->origin = tu_create(0, 0, 0, POINT);
	co->miny = -1;
	co->maxy = 0;
	co->cap = 0;
	obj->type = CONE;
	obj->material = m_create(tu_create(1,1,1,2));
	obj->transform = ma_identity(4);
	obj->obj = co;
	return(obj);
}

void	co_parse(char *str, t_mini *rt)
{
	t_object	*obj;
	char	**infos;
	int	length;
	double	a;

	printf("Cone\n");
	rt->parse_infos = ft_split(str, ' ', &length);
	infos = rt->parse_infos;
	if (length != 6 || ft_strncmp(infos[0], "co", 3))
		terminate("Incorrect scene file\n", rt);
	obj = co_create(rt);
	a = ft_atod(infos[3], rt) / 2;
	obj->transform = rodrigues_formula(tu_parse(infos[2], 0, rt), tu_create(0, 1, 0, VECTOR));
  obj->transform = ma_multiply(obj->transform,
			ma_translate(tu_parse(infos[1], 1, rt)));
	obj->transform = ma_multiply(obj->transform,
			ma_scale(tu_create(a, ft_atod(infos[4], rt), a, 1)));
	obj->material = m_create(tu_parse(infos[5], 2, rt));
	obj->id = rt->scene.count;
	rt->scene.objs[rt->scene.count] = obj;
	rt->scene.count++;
	free_double(rt->parse_infos);
	rt->parse_infos = NULL;
}

t_intersections	check_caps(t_object *co, t_ray ray, t_intersections xs)
{
	t_cone	*obj;
	double	t;
	double	x;
	double	z;

	obj = (t_cone *)co->obj;
	if (!obj->cap || fabs(ray.direction.y) < EPS)
		return (xs);
	t = (obj->miny - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= fabs(ray.origin.y + t * ray.direction.y))
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = t;
	}
	t = (obj->maxy - ray.origin.y) / ray.direction.y;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((x * x + z * z ) <= fabs(ray.origin.y + t * ray.direction.y))
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = t;
	}
	return (xs);
}

static void  co_util(t_intersections *xs, double c, t_ray ray, t_object *co)
{
	double y;
	t_cone	*obj;

	obj = (t_cone *)co->obj;
	y = ray.origin.y + c * ray.direction.y;
	if ( y > obj->miny && y < obj->maxy)
	{
		xs->inter[xs->count].object = co;
		xs->inter[xs->count++].t = c;
	}
}

t_intersections	co_intersect(t_object *co, t_ray ray, t_intersections xs)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = pow(ray.direction.x, 2) - pow(ray.direction.y, 2) + pow(ray.direction.z, 2);
	b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y + 2 * ray.origin.z * ray.direction.z;
	c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2) + pow(ray.origin.z, 2);
	if (fabs(a) < EPS && fabs(b) < EPS )
		return (xs);
	else if (fabs(a) < EPS)
	{
		xs.inter[xs.count].object = co;
		xs.inter[xs.count++].t = -c / (2 * b);
		return (check_caps(co, ray, xs));
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (check_caps(co, ray, xs));
	c = (-b - sqrt(disc)) / (2 * a);
	co_util(&xs, c, ray, co);
	c = (-b + sqrt(disc)) / (2 * a);
	co_util(&xs, c, ray, co);
	return (check_caps(co, ray, xs));
}
