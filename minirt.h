#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include "./Get_next_line/get_next_line.h"

# define ERR_USAGE "Usage : ./minirt Map_file(file.rt)"
# define ERR_MAP "Incorrect Map file"
# define ERR_CON "Minirt initialization failure"
# define ERR_WIN "Window initialization failure"
# define ERR_IMG "Image initialization failure"
# define ERR_MALLOC "Allocation failure"
# define USR_INT "User interruption"

# define BLACK 0x00000000
# define GREEN 0x0000FF00
# define RED 0xFF000000

# define DIS_WIDTH 700
# define DIS_LENGTH 700
# define VECTOR 0
# define POINT 1
# define COLOR 2
# define EPS 0.00001
# define PI 3.14

typedef struct s_bresen
{
	int	dx;
	int	dy;
	int	error[2];
	int	sx;
	int	sy;
}		t_bresen;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	int		w;
}	t_tuple;

typedef t_tuple t_point;
typedef t_tuple t_vector;
typedef t_tuple t_color;

typedef struct s_matrix
{
	double	v[4][4];
	int	rows;
	int	cols;
}	t_matrix;

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_sphere
{
	int	count;
	int	id;
	t_tuple	origin;
	double	radius;
	t_material	material;
	t_matrix transform;
}	t_sphere;

typedef struct s_cylinder
{
	int	count;
	int	id;
	t_tuple	origin;
	double	radius;
	int	cap;
	double	miny;
	double	maxy;
	t_material	material;
	t_matrix	transform;
}	t_cylinder;

typedef struct s_intersect
{
	int	object;
	double	t;
}	t_intersect;

typedef struct s_intersections
{
	int	count;
	t_intersect	x[20];
}	t_intersections;

typedef struct s_light
{
	int	count;
	int	type;
	t_tuple	intensity;
	t_tuple	position;
}	t_light;

typedef struct s_scene
{
	t_light	*light;
	t_sphere	*sp;
	t_cylinder	*cy;
}	t_scene;

typedef struct s_mini
{
	void	*con;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		length;
	t_scene	scene;
//	int		scale;
	//int		offset[2];
	//int		z_divisor[3];
	//double	angle[3];
}			t_mini;


void	start_display(t_mini *rt);
t_tuple	tu_create(double x, double y, double z, int type);
int	tu_compare(t_tuple t1, t_tuple t2);
t_tuple	tu_scale(t_tuple t1, double a);
double	tu_magnitude(t_tuple t1);
t_tuple	tu_normalize(t_tuple t1);
t_tuple	tu_add(t_tuple t1, t_tuple t2);
t_tuple	tu_subtract(t_tuple t1, t_tuple t2);
t_tuple	tu_cross(t_tuple t1, t_tuple t2);
double	tu_dot(t_tuple t1, t_tuple t2);
t_tuple	tu_multiply(t_tuple t1, t_tuple t2);
t_matrix	ma_create(int a, int b, double v[4][4]);
t_matrix	ma_multiply(t_matrix a, t_matrix b);
t_tuple	ma_tu_multiply(t_matrix m, t_tuple t);
t_matrix	ma_transpose(t_matrix m1);
double	ma_determinant(t_matrix m1);
t_matrix	ma_submatrix(t_matrix m1, int row, int col);
double	ma_cofactor(t_matrix m, int row, int col);
t_matrix	ma_invert(t_matrix m);
t_matrix	ma_identity(int size);
t_matrix	ma_translate(double x, double y, double z);
t_matrix	ma_scale(double x, double y, double z);
t_matrix	ma_rotate(double radian, int axis);
t_matrix	ma_shear(double pro[6]);
t_ray	ra_create(t_tuple origin, t_tuple direction);
t_tuple	ra_position(t_ray ray, double t);
t_ray	ra_transform(t_ray ray, t_matrix matrix);
t_mini	sp_create(char *str, t_mini rt);
t_sphere	sp_transform(t_sphere sp, t_matrix matrix);
t_intersections	sp_intersect(t_sphere sp, t_ray ray, t_intersections inter);
t_intersect	hits(t_intersections inter);
t_tuple	ve_camera(t_ray ray);
t_tuple	ve_light(t_tuple o_pos, t_tuple l_pos);
t_tuple	ve_sp_normal(t_sphere sp, t_tuple w_point);
t_tuple	ve_cy_normal(t_cylinder cy, t_tuple w_point);
t_tuple	ve_reflection(t_tuple in, t_tuple normal);
void	li_create(char *str, t_mini *rt);
t_material	m_create(t_tuple color);
t_color	lighting(t_material material, t_light light, t_point point, t_vector eyev, t_vector normalv);
t_scene	w_create(t_light light[10], t_sphere sp[10]);
t_intersections	w_intersect(t_scene scene, t_ray ray);
t_intersections	cy_intersect(t_cylinder cy, t_ray ray, t_intersections inter);
void	cy_create(char *str, t_mini *rt);
double	ft_atod(const char *str);
t_mini	parse(char *file, t_mini rt);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ca_create(char *str, t_mini *rt);
void	pl_create(char *str, t_mini *rt);
t_tuple	tu_parse(char *str, int type);
char	**ft_split(char const *s, char c, int *length);
void	free_double(char **ptr);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

void	terminate(char *error, t_mini *rt);

void	print_tuple(t_tuple t1);
void	print_matrix(t_matrix m1);
void	print_ray(t_ray r1);
#endif
