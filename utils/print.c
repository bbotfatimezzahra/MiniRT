#include "../minirt.h"

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

void	print_material(t_material ma)
{
	printf("	material : spec : %.1f refl : %.1f shine : %.1f pattern : ", ma.specular, ma.reflective, ma.shininess);
	if (ma.pattern.type == NONE)
		printf("NONE ");
	else if (ma.pattern.type == CHECKER)
		printf("CHECKERBOARD ");
	else if (ma.pattern.type == STRIPE)
		printf("STRIPE ");
	else if (ma.pattern.type == RING)
		printf("RING ");
	else if (ma.pattern.type == GRADIENT)
		printf("GRADIENT ");
	printf("color : ");
	print_tuple(ma.color);
}

void	print_scene(t_mini rt)
{
	int	i;

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
		print_material(rt.scene.objs[i]->material);
		printf("	transform : ");
		print_matrix(rt.scene.objs[i]->transform);
		printf("--------------------------\n");
	}
	printf("**************************************************\n");
}
