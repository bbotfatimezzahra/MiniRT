#include "../minirt.h"

int	ft_isfloat(char *str, int vector)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (!i || (str[i] && str[i] != '.' && !vector))
		return (0);
	if (str[i] && str[i] == '.')
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] && vector && str[i] == ',')
		return (1);
	else if (str[i])
		return (0);
	return (1);
}

void	check_vector(t_tuple tuple, int type, t_mini *rt)
{
	double	min;
	double	max;

	if (!type && !tuple.x && !tuple.y && !tuple.z)
		terminate("Incorrect scene file", rt);
	if (type == 0)
	{
		min = -1;
		max = 1;
	}
	else if (type == 2)
	{
		min = 0;
		max = 255;
	}
	else
		return;
	if (tuple.x < min || tuple.x > max
			|| tuple.y < min || tuple.y > max
			|| tuple.z < min || tuple.z > max)
		terminate("Incorrect scene file", rt);
}

t_tuple	tu_parse(char *str, int type, t_mini *rt)
{
	double	coord[3];
	t_tuple	tuple;
	char	*num;

	coord[0] = ft_atod(str, rt, 1);
	num = ft_strchr(str, ',', 1);
	if (!num || !ft_isdigit(num[1]))
		terminate("Incorrect scene file", rt);
	coord[1] = ft_atod(&num[1], rt, 1);
	num = ft_strchr(str, ',', 2);
	if (!num || !ft_isdigit(num[1]))
		terminate("Incorrect scene file", rt);
	coord[2] = ft_atod(&num[1], rt, 1);
	if (ft_strchr(str, ',', 3))
		terminate("Incorrect scene file", rt);
	tuple = tu_create(coord[0], coord[1], coord[2], type);
	check_vector(tuple, type, rt);
	if (type == 2)
		tuple = tu_create(tuple.x/255, tuple.y/255, 
				tuple.z/255, 2);
	return (tuple);
}

double	check_ratio(double value, int type, t_mini *rt)
{
	if (type == 2)
		return (value);
	if (value < 0 || (type  == 0 && value > 1)
			|| (type == 1 && value > 180)
			|| (type == 3 && value > 200))
		terminate("Incorrect scene file", rt);
	if (type == 1)
		value = value * PI / 180;
	return (value);
}
