#include "minirt.h"

t_matrix	ma_identity(int size)
{
	t_matrix	r;
	int	i;
	int	j;

	r = ma_create(size, size, NULL);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (i == j)
				r.v[i][j] = 1;
		}
	}
	return (r);
}

t_matrix	ma_translate(t_tuple tuple)
{
	t_matrix	r;

	r = ma_identity(4);
	r.v[0][3] = tuple.x;
	r.v[1][3] = tuple.y;
	r.v[2][3] = tuple.z;
	return (r);
}

t_matrix	ma_scale(t_tuple tuple)
{
	t_matrix	r;

	r = ma_identity(4);
	r.v[0][0] = tuple.x;
	r.v[1][1] = tuple.y;
	r.v[2][2] = tuple.z;
	return (r);
}

t_matrix	ma_rotate(double radian, int axis)
{
	t_matrix	r;

	r = ma_identity(4);
	if (!axis)
	{
		r.v[1][1] = cos(radian);
		r.v[1][2] = -sin(radian);
		r.v[2][1] = sin(radian);
		r.v[2][2] = cos(radian);
	}
	else if (axis == 1)
	{
		r.v[0][0] = cos(radian);
		r.v[0][2] = sin(radian);
		r.v[2][0] = -sin(radian);
		r.v[2][2] = cos(radian);
	}
	else
	{
		r.v[0][0] = cos(radian);
		r.v[0][1] = -sin(radian);
		r.v[1][0] = sin(radian);
		r.v[1][1] = cos(radian);
	}
	return (r);
}

t_matrix	ma_shear(double pro[6])
{
	t_matrix	r;

	r = ma_identity(4);
	r.v[0][1] = pro[0];
	r.v[0][2] = pro[1];
	r.v[1][0] = pro[2];
	r.v[1][2] = pro[3];
	r.v[2][0] = pro[4];
	r.v[2][1] = pro[5];
	return (r);
}
