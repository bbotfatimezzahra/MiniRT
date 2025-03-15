#include "minirt.h"


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

