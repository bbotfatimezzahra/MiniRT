#include "minirt.h"

void	cy_create(char *str, t_mini *rt)
{
	t_cylinder	cy;

	printf("Cyllinder\n");
	(void)str;
	(void)rt;
	cy.id = 1;
	cy.radius = 1;
	cy.origin = tu_create(0, 0, 0, POINT);
	cy.miny = -DIS_LENGTH;
	cy.maxy = DIS_LENGTH;
	cy.cap = 0;
	cy.material = m_create(tu_create(1,1,1,2));
	cy.transform = ma_identity(4);
	(void)cy;
}

