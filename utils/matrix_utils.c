/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:11:38 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 13:13:14 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_matrix	ma_transpose(t_matrix m)
{
	t_matrix	r;
	int			i;
	int			j;

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
	int		j;

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
	int			i;
	int			j;
	int			k;
	int			l;

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

	cof = ma_determinant(ma_submatrix(m, row, col));
	if ((row + col) % 2 == 1)
		cof *= -1;
	return (cof);
}

t_matrix	ma_invert(t_matrix m)
{
	t_matrix	r;
	double		det;
	int			i;
	int			j;

	det = ma_determinant(m);
	if (!det)
		return (m);
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
