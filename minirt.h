#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <float.h>
# include "mlx.h"
# include "./utils/Get_next_line/get_next_line.h"

# define ERR_USAGE "Usage : ./minirt Scene_file.rt"
# define ERR_SCENE "Incorrect Scene file"
# define ERR_CON "Minirt initialization failure"
# define ERR_WIN "Window initialization failure"
# define ERR_IMG "Image initialization failure"
# define ERR_MALLOC "Allocation failure"

# define BLACK 0x00000000
# define GREEN 0x0000FF00
# define RED 0xFF000000

# define DIS_WIDTH 1000
# define DIS_LENGTH 1000
# define VECTOR 0
# define POINT 1
# define COLOR 2
# define SPHERE 0
# define CYLINDER 1
# define PLANE 2
# define CONE 3
# define EPS 0.00001
# define PI 3.1415


typedef enum  e_pattern_type
{
	NONE,
  STRIPE,
  GRADIENT,
  RING,
  CHECKER
} t_pattern_type;

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
	t_point	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_pattern
{
  bool enable;
  t_pattern_type type; 
  t_matrix transform;
  t_color a;
  t_color b;
} t_pattern;

typedef struct s_material
{
	t_color	color;
	t_pattern pattern;
	double	diffuse;
	double	specular;
	double	shininess;
	double reflective;
}	t_material;

typedef struct s_sphere
{
	int	count;
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_cylinder
{
	int	count;
	t_point	origin;
	double	radius;
	int	cap;
	double	miny;
	double	maxy;
}	t_cylinder;

typedef struct s_cone
{
	int	count;
	t_point	origin;
	double	radius;
	int	cap;
	double	miny;
	double	maxy;
}	t_cone;

typedef	struct s_object
{
	int	id;
	int	type;
	void	*obj;
	t_material	material;
	t_matrix	transform;
}	t_object;

typedef struct s_intersect
{
	t_object	*object;
	double	t;
}	t_intersect;

typedef struct s_intersections
{
	int	count;
	t_intersect	inter[1024];
}	t_intersections;


typedef struct s_light
{
	int	count;
	t_color	intensity;
	t_point	position;
}	t_light;

typedef struct s_camera
{
  double horizontal_size;
  double vertical_size;
  double half_width;
  double half_hight;
  double pixel_size;
  t_matrix transform;
}	t_camera;

typedef struct s_scene
{
	t_light	**light;
	int	numlight;
	t_object	**objs;
	int	count;
	t_camera	*camera;
	t_color	*ambient;	
}	t_scene;

typedef struct s_compute
{
  t_object *obj;
  t_point point;
  t_vector eyev;
  t_vector normalv;
  t_vector reflectv;
  bool  inside;
  t_intersect xs;
  t_point under_point;
  t_point above_point; // it for the "acne shadow" case
} t_compute;

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
	char	*parse_str;
	char	**parse_elems;
	char	**parse_infos;
}			t_mini;


void	start_display(t_mini *rt);
//---------------------------------- Math -------------------------------------

t_matrix rodrigues_formula(t_vector orient, t_vector ini_vector);

//----------------------------tuple and matrix manipulation -------------------

t_tuple   tu_create(double x, double y, double z, int type);
int       tu_compare(t_tuple t1, t_tuple t2);
t_tuple   tu_scale(t_tuple t1, double a);
double    tu_magnitude(t_tuple t1);
t_tuple   tu_normalize(t_tuple t1);
t_tuple   tu_add(t_tuple t1, t_tuple t2);
t_tuple   tu_subtract(t_tuple t1, t_tuple t2);
t_tuple   tu_cross(t_tuple t1, t_tuple t2);
double    tu_dot(t_tuple t1, t_tuple t2);
t_tuple   tu_multiply(t_tuple t1, t_tuple t2);
t_matrix	ma_create(int a, int b, double v[4][4]);
t_matrix	ma_multiply(t_matrix a, t_matrix b);
t_tuple   ma_tu_multiply(t_matrix m, t_tuple t);
t_matrix	ma_transpose(t_matrix m1);
double    ma_determinant(t_matrix m1);
t_matrix	ma_submatrix(t_matrix m1, int row, int col);
double    ma_cofactor(t_matrix m, int row, int col);
t_matrix	ma_invert(t_matrix m);
t_matrix	ma_identity(int size);
t_matrix	ma_translate(t_tuple tuple);
t_matrix	ma_scale(t_tuple tuple);
t_matrix	ma_rotate(double radian, int axis);
t_matrix	ma_shear(double pro[6]);
t_matrix ma_tu_fill(t_tuple r1, t_tuple r2, t_tuple r3, t_tuple r4);

//----------------------------ray manipulation-----------------------------------

t_ray   ray_create(t_point origin, t_vector direction);
t_point ray_position(t_ray ray, double t);
t_ray   ray_transform(t_ray ray, t_matrix matrix);

//--------------------------ray-object intersection------------------------------

t_intersections pl_intersect(t_ray r, t_object *pl);
t_intersections sp_intersect(t_object *sp, t_ray ray, t_intersections xs);
t_intersections cy_intersect(t_object *cy, t_ray ray, t_intersections xs);
t_intersections co_intersect(t_object *co, t_ray ray, t_intersections xs);
t_intersections w_intersect(t_scene scene, t_ray ray);
t_intersect     hit(t_intersections inter);
t_intersections intersect_world(t_scene s, t_ray r);

//------------------------- compute lighting utils ------------------------------

void	ve_co_normal(t_point obj_point, t_vector *wrd_n, t_vector obj_n, t_object obj);
void      ve_cy_normal(t_point obj_point, t_vector *wrd_n, t_vector obj_n, t_object obj);
t_vector  ve_reflection(t_point in, t_vector normal);
t_tuple   ve_normal_at(t_object *obj, t_tuple point);
t_compute prepare(t_intersections xs, t_ray ray);

//------------------ lighting , shading, reflection, refraction ------------------

t_color         shade_hit(t_scene, t_compute cmp, int reflect_recur_checker);
bool            pixel_is_shadow(t_scene s, t_tuple above_point, int i);
t_color color_at(t_scene s, t_ray r, int reflect_recur_checker);
t_color	reflect_color(t_compute cmp, t_scene s, int reflect_recur_checker);
unsigned long rgb_to_hex(t_color c);
t_color	lighting(t_scene s, t_compute cmp, t_light light, bool shade);

//-------------------------------- Patterns --------------------------------------

t_color pattern_obj(t_pattern pat, t_object obj, t_point point);
t_color ring_pattern(t_pattern pat, t_point point);
t_color gradient_pattern(t_pattern pat, t_point point);
t_color strip_pattern(t_pattern pat, t_point point);
t_pattern new_pattern(void);

//------------------------------- Render scene ------------------------------------

void	put_pixel(t_mini *rt, int x, int y, int color);
void  render_scene(t_mini *mini);
t_camera  set_camera(double hsize, double vsize, double fov);
t_matrix view_transform(t_point from, t_vector orientation);

//------------------------- Parsing and initialization ----------------------------

void      sp_parse(char *str, t_mini *rt);
t_object	*sp_create(t_mini *rt);
t_vector	ve_camera(t_ray ray);
t_vector	ve_light(t_point o_pos, t_point l_pos);
void	    li_create(char *str, t_mini *rt);
void	    am_create(char *str, t_mini *rt);
t_material	m_create(t_color color);
t_scene	w_create(t_light light[10], t_sphere sp[10]);
t_object	*cy_create(t_mini *rt);
void	cy_parse(char *str, t_mini *rt);
void	co_parse(char *str, t_mini *rt);
t_object	*co_create(t_mini *rt);
void	parse_file(char *file, t_mini *rt);
void	ca_create(char *str, t_mini *rt);
void	pl_parse(char *str, t_mini *rt);
t_tuple	tu_parse(char *str, int type, t_mini *rt);
double	check_ratio(double value, int type, t_mini *rt);
t_material	m_parse(t_mini *rt, t_material ma, int length, int i);

void	free_one(char *ptr);
void	free_double(char ***ptr);
void	terminate(char *error, t_mini *rt);

//-----------------------------libft functions-----------------------------------

int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c, int *length);
double	ft_atod(char *str, t_mini *rt, int vector);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isfloat(char *str, int vector);

//--------------------------for debugging purpose -------------------------------

void	print_tuple(t_tuple t1);
void	print_matrix(t_matrix m1);
void	print_ray(t_ray r1);
void	print_scene(t_mini rt);

#endif
