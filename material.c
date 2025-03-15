#include "minirt.h"

t_material	m_create(t_tuple color)
{
	t_material	ma;

	ma.color = color;
	ma.pattern.enable = false;
	ma.diffuse = 0.9;
	ma.specular = 0.7;
	ma.reflective = 0;  
	ma.shininess = 200;
	return (ma);
}
