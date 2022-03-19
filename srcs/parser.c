/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/18 01:51:33 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_spaces(char **argv)
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

// static t_args	philo_init(char **argv)
// {
// 	t_args	args;

// 	args.num_philos = ft_atoi(argv[1]);
// 	args.tm_die = ft_atoi(argv[2]);
// 	args.tm_eat = ft_atoi(argv[3]);
// 	args.tm_sleep = ft_atoi(argv[4]);
// 	args.num_tm_eat = ft_atoi(argv[5]);
// 	return (args);
// }

int main(int argc, char **argv)
{
	if (argc >= 5)
	{
		check_spaces(argv);
		// philo_init(argv);
		exec_threads(argv);
	}


}
