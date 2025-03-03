/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbbot <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:55:54 by fbbot             #+#    #+#             */
/*   Updated: 2025/02/23 19:20:49 by fbbot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_str(char *str)
{
	int	i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i];
		if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
				&& i < 2)
			i++;
		else if ((c < '0' || c > '9') && (c < 9 || c > 13)
				&& c != 32 && c != ',' && c != '.' && c != '-')
			return (0);
		i++;
	}
	return (1);
}

t_tuple	tu_parse(char *str, int type)
{
	double	coord[3];

	coord[0] = ft_atod(str);
	coord[1] = ft_atod(&ft_strchr(str, ',', 1)[1]);
	coord[2] = ft_atod(&ft_strchr(str, ',', 2)[1]);
	return (tu_create(coord[0], coord[1], coord[2], type));
}
	
void	create_scene(char *str, t_mini *rt)
{
	if (!check_str(str))
	{
		free(str);
		terminate("Scene file check error", rt);
	}
//	if (!ft_strncmp(str, "A", 1))
//		al_create(str, rt);
	if (!ft_strncmp(str, "C", 1))
		ca_create(str, rt);
	else if (!ft_strncmp(str, "L", 1))
		li_create(str, rt);
	else if (!ft_strncmp(str, "sp", 2))
		sp_create(str, rt);
	else if (!ft_strncmp(str, "cy", 2))
		cy_create(str, rt);
	else if (!ft_strncmp(str, "pl", 2))
		pl_create(str, rt);
	else if (!ft_strncmp(str, "\n", 1))
		return ;
	else
	{
		free(str);
		terminate("Scene file elements error",rt);
	}
	print_tuple(rt->scene.light.position);
	print_tuple(rt->scene.light.intensity);
	printf("count : %d \n",rt->scene.light.count);

}

t_mini	parse(char *file, t_mini rt)
{
	char	*str;
	int		fd;

	str = ft_strchr(file, '.', 1);
	if (!str || ft_strncmp(str, ".rt", 4))
		terminate(ERR_USAGE, &rt);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		terminate("Open failure", &rt);
	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		terminate("Empty scene file", &rt);
	}
	while (str)
	{
		create_scene(str, &rt);
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (rt);
}
