#include "../minirt.h"

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
	return (0);
}
