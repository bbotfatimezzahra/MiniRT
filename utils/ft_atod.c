/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:11:06 by fbbot             #+#    #+#             */
/*   Updated: 2025/03/17 12:48:46 by misslunet        ###   ########.fr       */
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
		if (result > INT_MAX)
			terminate("Out Of Range Double Value", rt);
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
		if (((result > INT_MAX) && sign == 1)
			|| ((result * -1 > INT_MIN) && sign == -1))
			terminate("Out Of Range Double Value", rt);
	}
	return (float_point(result * sign, &str[i], rt));
}
