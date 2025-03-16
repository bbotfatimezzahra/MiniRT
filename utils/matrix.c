/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:09:14 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 14:52:52 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	ma_create(int rows, int cols, double v[4][4])
{
	t_matrix	r;
	int			i;
	int			j;

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

t_matrix	ma_tu_fill(t_tuple r1, t_tuple r2, t_tuple r3, t_tuple r4)
{
	t_matrix	new;

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

t_matrix	ma_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix	r;
	int			i;
	int			j;
	int			k;

	if (m1.cols != m2.rows)
		return (printf("MATRIX MATRIX MULTIPLY ERROR\n"), r);
	r = ma_create(fmin(m1.rows, m2.rows), fmin(m1.cols, m2.cols), NULL);
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

//if its possible we should protect the return of these functions
t_tuple	ma_tu_multiply(t_matrix m, t_tuple t)
{
	t_tuple	r;
	int		i;
	double	a[4];

	if (m.cols != 4)
		return (printf("MATRIX TUPLE MULTIPLY ERROR\n"), r);
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
