/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:03:36 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 14:04:15 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Require at least 2 forks to eat sir!\n");
		return (1);
	}
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
