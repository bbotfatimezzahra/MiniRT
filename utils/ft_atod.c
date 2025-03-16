/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:11:06 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/16 15:03:33 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}

int	ft_isdigit(int c)
{
	if ((c < '0' || c > '9') && c != '-')
		return (0);
	return (1);
}

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

double	float_point(double num, char *str, t_mini *rt)
{
	long double	result;
	int			i;

	if (str[0] != '.')
		return (num);
	result = 0;
	i = 1;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		if ((result >= 0 && (result + num > DBL_MAX))
			|| (result < 0 && (result + num < DBL_MIN)))
			terminate("Out Of Range Double Value 2", rt);
		i++;
	}
	result = result * pow(10, -(i - 1));
	return (num + result);
}

double	ft_atod(char *str, t_mini *rt, int a)
{
	long double	result;
	int			sign;
	int			i;

	if (!str || !ft_isfloat(str, a))
		terminate("Incorrect Double Value", rt);
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
		if (((result > DBL_MAX) && sign == 1)
			|| ((result * -1 > DBL_MIN) && sign == -1))
			terminate("Out Of Range Double Value 1", rt);
	}
	return (float_point(result * sign, &str[i], rt));
}
