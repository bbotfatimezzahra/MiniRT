#include "minirt.h"

t_material	m_create(t_tuple color)
{
	t_material	ma;

	ma.color = color;
  ma.pattern.enable = false;
	ma.ambient = 0.2;
	ma.diffuse = 0.9;
	ma.specular = 0.9;
  ma.reflective = 0;  
	ma.shininess = 200;
	return (ma);
}
