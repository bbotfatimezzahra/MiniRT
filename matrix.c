#include "minirt.h"

t_matrix ma_tu_fill(t_tuple r1, t_tuple r2, t_tuple r3, t_tuple r4)
{
  t_matrix new;

  new.rows = 4;
  new.cols = 4;
  new.v[0][0] = r1.x;
  new.v[0][1] = r1.y;
  new.v[0][2] = r1.z;
  new.v[0][3] = r1.w;
  new.v[1][0] = r2.x;
  new.v[1][1] = r2.y;
  new.v[1][2] = r2.z;
  new.v[1][3] = r2.w;
  new.v[2][0] = r3.x;
  new.v[2][1] = r3.y;
  new.v[2][2] = r3.z;
  new.v[2][3] = r3.w;
  new.v[3][0] = r4.x;
  new.v[3][1] = r4.y;
  new.v[3][2] = r4.z;
  new.v[3][3] = r4.w;
  return (new);
}

t_matrix	ma_create(int rows, int cols, double v[4][4])
{
	t_matrix	r;
	int	i;
	int	j;

	r.rows = rows;
	r.cols = cols;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (!v)
				r.v[i][j] = 0;
			else
				r.v[i][j] = v[i][j];
		}
	}
	return (r);
}

t_matrix	ma_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix	r;
	int	i;
	int	j;
	int	k;

	if (m1.cols != m2.rows)
		return (printf("ERROR\n"), r);
	r = ma_create(fmin(m1.rows ,m2.rows), fmin(m1.cols ,m2.cols), NULL);
	i = -1;
	while (++i < r.rows)
	{
		j = -1;
		while (++j < r.cols)
		{
			r.v[i][j] = 0;
			k = -1;
			while (++k < r.rows)
				r.v[i][j] += m1.v[i][k] * m2.v[k][j]; 
		}
	}
	return (r);
}

t_matrix	ma_transpose(t_matrix m)
{
	t_matrix	r;
	int	i;
	int	j;

	r = ma_create(m.rows, m.cols, NULL);
	i = -1;
	while (++i < r.rows)
	{
		j = -1;
		while (++j < r.cols)
			r.v[j][i] = m.v[i][j];
	}
	return (r);
}

double	ma_determinant(t_matrix m)
{
	double	det;
	int	j;

	if (m.rows == 2 && m.cols == 2)
		det = m.v[0][0] * m.v[1][1] - m.v[0][1] * m.v[1][0];
	else
	{
		det = 0;
		j = -1;
		while (++j < m.cols)
			det += m.v[0][j] * ma_cofactor(m, 0, j);
	}
	return (det);
}

t_matrix	ma_submatrix(t_matrix m, int row, int col)
{
	t_matrix	r;
	int	i;
	int	j;
	int	k;
	int	l;

	r = ma_create(m.rows - 1, m.cols - 1, NULL);
	i = -1;
	k = -1;
	while (++i < 4)
	{
		j = -1;
		l = -1;
		if ((i != row) && (++k < r.rows))
		{
			while (++j < 4)
			{
				if ((j != col) && (++l < r.cols))
					r.v[k][l] = m.v[i][j];
			}
		}
	}
	return (r);
}

double	ma_cofactor(t_matrix m, int row, int col)
{
	double	cof;

  /*printf("hi\n\n\n");*/
	cof = ma_determinant(ma_submatrix(m, row, col));
	if ((row + col) % 2 == 1)
		cof *= -1;
	return (cof);
}

t_matrix	ma_invert(t_matrix m)
{
	t_matrix	r;
	double	det;
	int	i;
	int	j;

	det = ma_determinant(m);
	/*if (!det)*/
	/*	return (m);*/
	r = ma_create(m.rows, m.cols, NULL);
	i = -1;
	while (++i < m.rows)
	{
		j = -1;
		while (++j < m.cols)
		{
			r.v[i][j] = ma_cofactor(m, i, j);
			r.v[i][j] /= det;
		}
	}
	r = ma_transpose(r);
	return (r);
}

t_tuple	ma_tu_multiply(t_matrix m, t_tuple t)
{
	t_tuple	r;
	int	i;
	double	a[4];

	if (m.cols != 4)
		return (printf("ERROR\n"), r);
	i = -1;
	while (++i < 4)
	{
		a[i] = m.v[i][0] * t.x;
		a[i] += m.v[i][1] * t.y;
		a[i] += m.v[i][2] * t.z;
		a[i] += m.v[i][3] * t.w;
	}
	r.x = a[0];
	r.y = a[1];
	r.z = a[2];
	r.w = a[3];
	return (r);
}
