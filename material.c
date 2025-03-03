#include "minirt.h"

t_material	m_create(t_tuple color)
{
	t_material	ma;

	ma.color = color;
	ma.ambient = 0.1;
	ma.diffuse = 0.9;
	ma.specular = 0.9;
	ma.shininess = 200;
	return (ma);
}
