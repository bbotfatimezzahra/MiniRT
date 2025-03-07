#include "minirt.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	i = 0;
	if (!n)
		return (0);
	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	while (tmps1[i] && tmps2[i] && (i < n - 1) && (tmps1[i] == tmps2[i]))
		i++;
	return (tmps1[i] - tmps2[i]);
}


double	ft_atoi(const char *str)
{
	long double	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 2147483647)
			return (0);
		i++;
	}
	result = result * pow(10, -i);
	return (result);
}

double	ft_atod(const char *str)
{
	long double	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i++] - '0');
		if ((result > DBL_MAX) && sign == 1)
			return (0);
		else if ((result * -1 > DBL_MIN) && sign == -1)
			return (0);
	}
	if (str[i] == '.')
		result += ft_atoi(&str[i + 1]);
	return (result * sign);
}
