#include "../minirt.h"


t_matrix  transf_ma(double thetha, t_matrix u_cross, t_matrix u_cross_squared);

t_matrix rodrigues_formula(t_vector final_dir, t_vector ini_vector)
{
  t_vector u;
  double thetha;
  t_matrix u_cross;
  t_matrix u_cross_squared;

  final_dir = tu_normalize(final_dir);
  u = tu_cross(ini_vector, final_dir);
  if (tu_magnitude(u) == 0)
    return (ma_identity(4));
  u = tu_normalize(u);
  thetha = acos(tu_dot(ini_vector, final_dir));
  u_cross = ma_tu_fill(tu_create(0, -u.z, u.y, 0), tu_create(u.z, 0, -u.x, 0)
                    , tu_create(-u.y, u.x, 0, 0), tu_create(0, 0, 0, 0));
  u_cross.rows = 3; 
  u_cross.cols = 3; 
  u_cross_squared = ma_multiply(u_cross, u_cross);
  return (transf_ma(thetha, u_cross, u_cross_squared));
}

t_matrix  transf_ma(double thetha, t_matrix u_cross, t_matrix u_cross_squared)
{
  int i;
  int j;
  int k;
  t_matrix trans_ma;

  i = 0;
  trans_ma = ma_identity(4);
  while(i < 3)
  {
    j = 0;
    while (j < 3)
    {
      k = 0;
      if (i == j)
        k = 1;
      trans_ma.v[i][j] = k + sin(thetha) * u_cross.v[i][j]
        + (1 - cos(thetha)) * u_cross_squared.v[i][j];
      j++;
    }
    i++;
  }
  return (trans_ma);
}
