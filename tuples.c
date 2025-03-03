#include "minirt.h"

t_tuple	tu_create(double x, double y, double z, int w)
{
	t_tuple	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

int tu_compare(t_tuple t1, t_tuple t2)
{
	if (fabs(t1.x - t2.x) < EPS
		&& fabs(t1.y - t2.y) < EPS
		&& fabs(t1.z - t2.z) < EPS)
		return (1);
	return (0);
}

t_tuple tu_scale(t_tuple t1, double a)
{
	t_tuple	scaled;

	scaled.x = t1.x * a;
	scaled.y = t1.y * a;
	scaled.z = t1.z * a;
	scaled.w = t1.w * a;
	if (t1.w == 2)
		scaled.w = 2;
	return (scaled);
}

double	tu_magnitude(t_tuple t1)
{
	double	sx;
	double	sy;
	double	sz;
	double	sw;

	sx = pow(t1.x, 2);
	sy = pow(t1.y, 2);
	sz = pow(t1.z, 2);
	sw = pow(t1.w, 2);
	return (sqrt(sx + sy + sz + sw));
}

t_tuple	tu_normalize(t_tuple t1)
{
	t_tuple	norm;
	double	magn;

	magn = tu_magnitude(t1);
	norm.x = t1.x / magn;
	norm.y = t1.y / magn;
	norm.z = t1.z / magn;
	norm.w = t1.w / magn;
	return (norm);
}
