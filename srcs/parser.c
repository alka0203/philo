/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/28 17:35:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_spaces(char **argv)
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
		while (argv[i][j])
		{
			if (ft_isalnum(argv[i][j]))
			{
				flag = 1;
				break;
			}
			j++;
		}
		if (flag == 0)
			break;
		i++;
	}
	if (flag == 0)
	{
		printf("Enter actual values sir!\n");
		exit(EXIT_FAILURE);
	}
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

int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) <= 1)
	{
		printf("Require at least 2 forks to eat sir!\n");
		return 1;
	}
	return 0;
}

static int	check_num_args(char **argv, int i, int j, int k)
{
	if ((argv[i][j] < 48 || argv[i][j] > 57) && argv[i][j] != ' ')
	{
		printf("Enter numbers sir!\n");
		return (1);
	}
	else if (argv[i][j] >= 48 && argv[i][j] <= 57)
	{
		k = j;
		while (argv[i][k] >= 48 && argv[i][k] <= 57)
			k++;
		if (argv[i][k] == ' ')
		{
			while (argv[i][k] == ' ')
			{
				if (argv[i][k + 1] != ' ' && argv[i][k + 1] != 0)
				{
					printf("Error sir!\n");
					return (1);
				}
				k++;
			}
		}
	}
	return (0);
}

int	iter_args(char **argv)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	k = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (check_num_args(argv, i, j, k) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
