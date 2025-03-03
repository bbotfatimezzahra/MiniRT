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
	i = 0;
	while (i < m.rows)
	{
		j = 0;
		printf("|");
		while (j < m.cols)
		{
			printf(" %.5f |",m.v[i][j]);
			j++;
		}
		i++;
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
/*
int	main(int argc, char **argv)
{
	t_tuple	t1;
	t_tuple	t2;

	(void)argc;
	(void)argv;
	t1 = create(3, -2, 5, 1);
	printf("t1 : ");print_tuple(t1);
	t2 = create(-2, 3, 1, 0);
	printf("t2 : ");print_tuple(t2);
	printf("add : ");print_tuple(add(t1, t2));
	printf("subtract : ");print_tuple(subtract(t1, t2));
	printf("dot : %f\n",dot(t1, t2));
	printf("cross : ");print_tuple(cross(t1, t2));
	printf("magnitude : %f\n",magnitude(t1));
	printf("normalize : ");print_tuple(normalize(t1));
	printf("scale 2 : ");print_tuple(scale(t1, 2));
	printf("compare : %d\n",compare(t1, t2));
	start_display(rt);
	return (0);
}
*/
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
	li_create(NULL, &rt);
/*	rt.scale = 10;
	rt->z_divisor[0] = INT_MIN;
	rt->z_divisor[1] = INT_MAX;
	rt->z_divisor[2] = 1;
	rt->angle[0] = 0;
	rt->angle[1] = 0;
	rt->angle[2] = 0;*/
	return (rt);
}

int	main(int argc, char **argv)
{
	t_mini	rt;

	(void)argv;
	(void)argc;
	rt = init_mini();
	if (argc != 2)
		terminate(ERR_USAGE, &rt);
	rt = parse(argv[1], rt);
	printf("main\n");
	print_tuple(rt.scene.light.position);
	print_tuple(rt.scene.light.intensity);
	printf("count : %d \n",rt.scene.light.count);
/*
	start_display(&rt);
	t_matrix	a;
	t_matrix	b;
	t_matrix	c;
	
	float t1[4][4] = {{3,-9,7,3},{3,-8,2,-9},{-4,4,4,1},{-6,5,-1,1}};
	float t2[4][4] = {{8,2,2,2},{3,-1,7,0},{7,0,5,4},{6,-2,0,5}};
	a = ma_create(4, 4,t1);
	print_matrix(a);
	b = ma_create(4, 4,t2);
	print_matrix(b);
	printf("================================\n");
	c = ma_multiply(a,b);
	print_matrix(c);
	printf("================================\n");
	print_matrix(ma_multiply(c, ma_invert(b)));
	print_matrix(a);
	printf("COF = %.f \n",ma_cofactor(b, 0, 0));
	printf("COF = %.f \n",ma_cofactor(b, 0, 1));
	printf("COF = %.f \n",ma_cofactor(b, 0, 2));
	printf("DET = %.f \n",ma_determinant(b));
	printf("================================\n");
	printf("COF = %.f \n",ma_cofactor(a, 0, 0));
	printf("COF = %.f \n",ma_cofactor(a, 0, 1));
	printf("COF = %.f \n",ma_cofactor(a, 0, 2));
	printf("COF = %.f \n",ma_cofactor(a, 0, 3));
	printf("DET = %.f \n",ma_determinant(a));
	c = ma_invert(a);
	print_matrix(c);
	printf("================================\n");
	c = ma_invert(b);
	print_matrix(c);
	//printf("DET = %f \n",ma_determinant(b));

	printf("================================\n");
	printf("================================\n");
	t_tuple	d;
	float	pro[6] = {1, 0, 0, 0, 0, 0};
	d = tu_create(2, 3, 4, POINT);
	print_tuple(d);
	a = ma_shear(pro);
	print_matrix(a);
	print_tuple(ma_tu_multiply(a, d));
	printf("================================\n");
	float pri[6] = {0, 1, 0, 0, 0, 0};
	b = ma_shear(pri);
	print_matrix(b);
	print_tuple(ma_tu_multiply(b, d));
	printf("================================\n");
	float pra[6] = {0, 0, 1, 0, 0, 0};
	c = ma_shear(pra);
	print_matrix(c);
	print_tuple(ma_tu_multiply(c, d));
		d = tu_create(-4, 6, 8, VECTOR);
	print_tuple(d);
	c = ma_invert(a);
	print_tuple(ma_tu_multiply(c, d));
	printf("================================\n");
	print_tuple(ma_tu_multiply(a, d));
	printf("================================\n");
	
	t_tuple	a;
	t_tuple	b;
	t_ray	r;

	a = tu_create(1, 2, 3, POINT);
	print_tuple(a);
	b = tu_create(4, 5, 6, VECTOR);
	print_tuple(b);
	r = ra_create(a, b);
	print_ray(r);
	printf("================================\n");
	a = tu_create(2, 3, 4, POINT);
	print_tuple(a);
	b = tu_create(1, 0, 0, VECTOR);
	print_tuple(b);
	r = ra_create(a, b);
	print_ray(r);
	print_tuple(ra_position(r, 0));
	print_tuple(ra_position(r, 1));
	print_tuple(ra_position(r, -1));
	print_tuple(ra_position(r, 2.5));
	new = ra_transform(ray, ma_scale(2, 3, 4));
	print_ray(new);

	t_sphere	sp;

	sp = sp_create(tu_create(0,0,0,POINT), 1);
	sp = sp_transform(sp, ma_multiply(ma_scale(1, 0.5, 1),ma_rotate(PI / 5, 2)));
	print_tuple(ve_sp_normal(sp, tu_create(0, sqrt(2)/2, -sqrt(2)/2,POINT)));
//	print_tuple(tu_normalize(tu_create(sqrt(3/3),sqrt(3/3),sqrt(3/3),VECTOR)));
	*//*t_ray	ray;
//	t_ray	new;
	t_intersections	hit;

	ray = ra_create(tu_create(0,0,-5,POINT), tu_create(0,0,1,VECTOR));
	print_ray(ray);
	sp = sp_transform(sp, ma_translate(5, 0, 0));
	hit = intersect(sp, ray);
	printf("HIT t = %d \n",hit.count);
	
	print_tuple(ve_reflection(tu_create(1,-1,0,0), tu_create(0,1,0,0)));
	print_tuple(ve_reflection(tu_create(0,-1,0,0), tu_create(sqrt(2)/2,sqrt(2)/2,0,0)));

	t_material	mat;
	t_point	pos;
	t_vector	cam;
	t_vector	normal;
	t_light	light;

	mat = m_create();
	pos = tu_create(0, 0, 0, 1);
	cam = tu_create(0, 0, -1, 0);
	normal = tu_create(0, 0, -1, 0);
	light = li_create(tu_create(0, 0, 10, 1), tu_create(1, 1, 1, 2));
	print_tuple(lighting(mat, light, pos, cam, normal));

	t_cylinder	cy;
	t_ray	ray;
	t_intersections	hit;

	cy = cy_create();
	cy.miny = 1;
	cy.maxy = 2;
	cy.cap = 1;
	ray = ra_create(tu_create(0,-1,-2,POINT), tu_normalize(tu_create(0,1,1,VECTOR)));
	print_ray(ray);
	hit.count = 0;
	hit = cy_intersect(cy, ray, hit);
	printf("HIT count = %d \n",hit.count);
	printf("HIT t0 = %f \n",hit.x[0].t);
	printf("HIT t1 = %f \n",hit.x[1].t);
	print_tuple(ve_cy_normal(cy, tu_create(0, 1, 0,POINT)));
	print_tuple(ve_cy_normal(cy, tu_create(0.5, 1, 0,POINT)));
	print_tuple(ve_cy_normal(cy, tu_create(0, 1, 0.5,POINT)));
	print_tuple(ve_cy_normal(cy, tu_create(0, 2, 0,POINT)));
	print_tuple(ve_cy_normal(cy, tu_create(0.5, 2, 0,POINT)));
	print_tuple(ve_cy_normal(cy, tu_create(0, 2, 0.5,POINT)));
	*/
	return (0);
}
