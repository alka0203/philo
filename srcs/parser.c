/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/12 14:42:12 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_spaces()
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

int main(int argc, char **argv)
{
	if (argc >= 4)
	{
		check_spaces();
		if (ft_atoi(argv[1]) < 1)
			printf("Please input 1 or more number of philosophers\n");
		if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0)
			printf("Please enter a valid number for the time\n");
		if (argv[4])
		{
			if (ft_atoi(argv[4]) < 1 || !argv[4])
				printf("Please enter a valid number for the time\n");
		}
	}
	else
		printf("Please input more arguments!\n");
}
