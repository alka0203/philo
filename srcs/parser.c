/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 14:04:00 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	space_flag(char **argv, int i, int j, int flag)
{
	while (argv[i][j])
	{
		if (ft_isalnum(argv[i][j]))
		{
			flag = 1;
			break ;
		}
		j++;
	}
	return (flag);
}

int	check_spaces(char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	while (argv[i])
	{
		flag = 0;
		flag = space_flag(argv, i, j, flag);
		if (flag == 0)
			break ;
		i++;
	}
	if (flag == 0)
	{
		printf("Enter actual values sir!\n");
		return (1);
	}
	return (0);
}

static void	check_int(double r)
{
	if (r > 2147483647 || r < -2147483648)
	{
		ft_putstr("Error\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	double	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (i >= 10)
			check_int(r);
		r *= 10;
		r = r + (str[i] - '0');
		i++;
	}
	r *= s;
	return (r);
}
