#include "minirt.h"

void	print_tuple(t_tuple t)
{
	if (t.w == VECTOR)
		printf("VECTOR");
	else if (t.w == COLOR)
		printf("COLOR");
	else if (t.w == POINT)
		printf("POINT");
	printf("(%.5f, %.5f, %.5f)\n",t.x, t.y, t.z);
}

void	print_matrix(t_matrix m)
{
	int	i;
	int	j;

	printf("MATRIX :\n");
	i = -1;
	while (++i < m.rows)
	{
		j = -1;
		printf("|");
		while (++j < m.cols)
			printf(" %.5f |",m.v[i][j]);
		printf("\n");
	}
}

void	print_ray(t_ray r)
{
	printf("RAY (\nOg :");
	print_tuple(r.origin);
	printf("Dir :");
	print_tuple(r.direction);
}

void	print_scene(t_mini rt)
{
	int	i;
	t_material	material;

	printf("**************************************************\n");
	printf("		 ****Scene****\n");
	printf("=Camera :=\n");
	print_matrix(rt.scene.camera->transform);
	printf("======================================\n");
	printf("=Ambient :=\n");
	print_tuple(*rt.scene.ambient);
	printf("======================================\n");
	printf("=Lights := count %d \n", rt.scene.numlight);
	i = -1;
	while (++i < rt.scene.numlight)
	{
		printf("	num : %d\n	position :",i);
		print_tuple(rt.scene.light[i]->position);
		printf("	intensity :");
		print_tuple(rt.scene.light[i]->intensity);
		printf("--------------------------\n");
	}
	printf("======================================\n");
	printf("=Objects := count %d \n", rt.scene.count);
	i = -1;
	while (++i < rt.scene.count)
	{
		printf("	id : %d\n",rt.scene.objs[i]->id);
		printf("	type : ");
		if (rt.scene.objs[i]->type == SPHERE)
			printf("SPHERE\n");
		else if (rt.scene.objs[i]->type == CYLINDER)
			printf("CYLINDER\n");
		else if (rt.scene.objs[i]->type == PLANE)
			printf("PLANE\n");
		else if (rt.scene.objs[i]->type == CONE)
			printf("CONE\n");
		else
			printf("ELSE\n");
		printf("	obj : %p\n", rt.scene.objs[i]->obj);
		printf("	material : color ");
		material = rt.scene.objs[i]->material;
		print_tuple(material.color);
		printf("	transform : ");
		print_matrix(rt.scene.objs[i]->transform);
		printf("--------------------------\n");
	}
	printf("**************************************************\n");
}
