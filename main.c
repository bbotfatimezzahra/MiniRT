#include "minirt.h"

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
	rt.scene.numlight = 0;
	rt.scene.objs = NULL;
	rt.scene.count = 0;
	rt.scene.camera = NULL;
	rt.scene.ambient = NULL;
	rt.parse_str = NULL;
	rt.parse_elems = NULL;
	rt.parse_infos = NULL;
	return (rt);
}

int	main(int argc, char **argv)
{
	t_mini	rt;

	rt = init_mini();
	if (argc != 2)
		terminate(ERR_USAGE, &rt);
	parse_file(argv[1], &rt);
	print_scene(rt);
	start_display(&rt);
/*	t_intersections	xs;
	xs = co_intersect(co_create(&rt), ray_create(tu_create(0,0,-5,1),tu_normalize(tu_create(0,1,0,0))), xs);
			printf("count : %d   | t0 = %.5f   t1 = %.5f\n", xs.count, xs.inter[0].t, xs.inter[1].t);
			xs.count = 0;
	xs = co_intersect(co_create(&rt), ray_create(tu_create(0,0,-0.25,1),tu_normalize(tu_create(0,1,1,0))), xs);
			printf("count : %d   | t0 = %.5f   t1 = %.5f\n", xs.count, xs.inter[0].t, xs.inter[1].t);
			xs.count = 0;
	xs = co_intersect(co_create(&rt), ray_create(tu_create(0,0,-0.25,1),tu_normalize(tu_create(0,1,0,0))), xs);
			printf("count : %d   | t0 = %.5f   t1 = %.5f\n", xs.count, xs.inter[0].t, xs.inter[1].t);
				xs.count = 0;
	xs = co_intersect(co_create(&rt), ray_create(tu_create(0,0,-1,1),tu_normalize(tu_create(0,1,1,0))), xs);
			printf("count : %d   | t0 = %.5f   t1 = %.5f\n", xs.count, xs.inter[0].t, xs.inter[1].t);
			printf("===================================\n");
			t_vector w;
			t_vector obj_n;
			w = tu_create(0,0,0,0);
			ve_co_normal(tu_create(0,0,0,1), &w, obj_n, *co_create(&rt));
			ve_co_normal(tu_create(1,1,1,1), &w, obj_n, *co_create(&rt));
			ve_co_normal(tu_create(-1,-1,0,1), &w, obj_n, *co_create(&rt));
			*/
	return (0);
}
