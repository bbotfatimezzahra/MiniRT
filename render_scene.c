#include "minirt.h"

t_matrix view_transform(t_point from, t_vector orientation, t_vector up)
{
    t_vector forward;
    t_vector left;
    t_vector normalize_up;
    t_vector real_up;
    t_matrix orientation_matrix;
    

    forward = tu_normalize(orientation);
    normalize_up = tu_normalize(up);
    left = tu_cross(forward, normalize_up);
    left = tu_normalize(left);
    real_up = tu_cross(left, forward);
    orientation_matrix = ma_tu_fill(left, real_up, tu_negate(forward), tu_create(0, 0, 0, POINT));
    return (ma_multiply(orientation_matrix, ma_translate(tu_create(-from.x, -from.y, -from.z, 0))));
}

t_camera  set_camera(double hsize, double vsize, double fov)
{
  double half_view;
  float aspect;
  t_camera  c;
  // here we just use a sample trigonometry calcul here because we set the field of view
  // one unit so half_view/1 == half_view
  c.horizontal_size = hsize;
  c.vertical_size = vsize;
  c.transform = ma_identity(4);
  half_view = tan(fov / 2);
  aspect = hsize / vsize;
  // half width and half height is how mutch unit i am seeing the actual world
  if (aspect >= 1)
  {
    c.half_width = half_view;
    c.half_hight = c.half_width / aspect;
  }
  else
  {
    c.half_hight = half_view;
    c.half_width = aspect * c.half_hight;
  }
  // this represents how mutch units fits in one pixel
  c.pixel_size = (2 * c.half_width) / hsize;
  return (c);
}

// don't forget here we are assiming that our camera is in (0, 0, -1) so it's understoodk
t_ray ray_for_pixel(t_camera c, int px, int py)
{
  double xoffset;
  double yoffset;
  double x_world;
  double y_world;
  t_point transformed_pixel;
  t_ray r;

  xoffset = (px + 0.5) * c.pixel_size;
  yoffset = (py + 0.5) * c.pixel_size;
  x_world = c.half_width - xoffset;
  y_world = c.half_hight - yoffset;
  transformed_pixel = ma_tu_multiply(ma_invert(c.transform), tu_create(x_world, y_world, -1, 1));
  r.origin = ma_tu_multiply(ma_invert(c.transform), tu_create(0, 0, 0, 1));
  r.direction = tu_normalize(tu_subtract(transformed_pixel, r.origin));
  return (r);
}

void  render_a_scene(t_mini *mini)
{
  int i;
  int j;
  t_color colr;
  t_ray r;
  int reflect_recur_checker; // this variable is made to avoid recursivity in the case of two reflected obj

  i = 0;
  while (i < DIS_WIDTH)
  {
    j = 0;
    while (j < DIS_LENGTH)
    {
      r = ray_for_pixel(*mini->scene.camera, i, j);
      reflect_recur_checker = 0;
      colr = color_at(mini->scene, r, reflect_recur_checker);
      put_pixel(mini, i, j, rgb_to_hex(colr));
      j++;
    }
    i++;
  }
}

