/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/27 15:04:11 by asanthos         ###   ########.fr       */
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

static void	check_num(const char *str, int i)
{
	if (str[i] < 48 || str[i] > 57)
	{
		ft_putstr("Error\n");
		exit(EXIT_FAILURE);
	}
}
//look through parsing of letters after number in later args
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
	check_num(str, i);
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (i >= 10)
			check_int(r);
		r *= 10;
		r = r + (str[i] - '0');
		i++;
	}
	// if (str[i])
	// 	check_num(str, i);
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
			if ((argv[i][j] < 48 || argv[i][j] > 57) && argv[i][j] != ' ')
			{
				printf("Enter numbers sir!\n");
				return 1;
			}
			else if (argv[i][j] >= 48 && argv[i][j] <= 57)
			{
				k = j;
				while (argv[i][j] >= 48 && argv[i][j] <= 57)
				{
					if (argv[i][j] == ' ')
					{
						k++;
						if (argv[i][j + 1] != ' ' && argv[i][j] != 0)
							return 1;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return 0;
}

//fix "    12   12  "12
