#include "minirt.h"

t_material	m_create(t_tuple color)
{
	t_material	ma;

	ma.color = color;
	ma.pattern = new_pattern();
	ma.diffuse = 0.9;
	ma.specular = 0.7;
	ma.reflective = 0;  
	ma.shininess = 200;
	return (ma);
}

t_material	m_parse(t_mini *rt, t_material ma, int i)
{
	ma.specular = check_ratio(ft_atod(rt->parse_infos[i], rt, 0), 0, rt);
	ma.reflective = check_ratio(ft_atod(rt->parse_infos[++i], rt, 0), 0, rt);
	ma.shininess = check_ratio(ft_atod(rt->parse_infos[++i], rt, 0), 3, rt);
	ma.pattern.type = ft_atod(rt->parse_infos[++i], rt, 0);
	if (ma.pattern.type)
		ma.pattern.enable = true;
	return (ma);
}
