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

void	print_objs(t_mini rt)
{
	int	i;
	t_material	material;

	printf("**************************************************\n");
	printf("Scene :\n");
	printf("=Light := \n count %d \n position :", rt.scene.light->count);
	print_tuple(rt.scene.light->position);
	printf("intensity :");
	print_tuple(rt.scene.light->intensity);
	printf("Ambient :");
	print_tuple(*rt.scene.ambient);
	printf("Objects : count %d \n", rt.scene.count);
	i = -1;
	while (++i < rt.scene.count)
	{
		printf("id : %d\n",rt.scene.objs[i]->id);
		printf("type : ");
		if (rt.scene.objs[i]->type == SPHERE)
			printf("SPHERE\n");
		else if (rt.scene.objs[i]->type == CYLINDER)
			printf("CYLINDER\n");
		else if (rt.scene.objs[i]->type == PLANE)
			printf("PLANE\n");
		else
			printf("ELSE\n");
		printf("obj : %p\n", rt.scene.objs[i]->obj);
		printf("material : color ");
		material = rt.scene.objs[i]->material;
		print_tuple(material.color);
		printf("transform : ");
		print_matrix(rt.scene.objs[i]->transform);
		printf("=========================\n");
	}
	printf("**************************************************\n");
}

t_mini	init_mini(void)
{
	t_mini rt;

	rt.con = NULL;
	rt.win = NULL;
	rt.img = NULL;
	rt.addr = NULL;
	rt.bpp = 0;
	rt.line_length = 0;
	rt.endian = 0;
	rt.width = DIS_WIDTH;
	rt.length = DIS_LENGTH;
	rt.scene.light = NULL;
	rt.scene.objs = NULL;
	rt.scene.count = 0;
	rt.scene.camera = NULL;
	rt.scene.ambient = NULL;
	return (rt);
}

int	main(int argc, char **argv)
{
	t_mini	rt;

	rt = init_mini();
	if (argc != 2)
		terminate(ERR_USAGE, &rt);
	parse(argv[1], &rt);
	print_objs(rt);
	return (0);
}
