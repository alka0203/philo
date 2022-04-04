/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:13:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/03 15:17:12 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// static t_args	*args_init(char **argv)
// {
// 	t_args	*args;

// 	args = (t_args *)malloc(sizeof(t_args));
// 	args->num_philos = ft_atoi(argv[1]);
// 	args->tm_die = ft_atoi(argv[2]);
// 	args->tm_eat = ft_atoi(argv[3]);
// 	args->tm_sleep = ft_atoi(argv[4]);
// 	args->num_tm_eat = ft_atoi(argv[5]);
// 	return (args);
// }

int main(int argc, char **argv)
{
	// t_args	*args;

	if (argc == 5)
	{
		// args = args_init(argv);
		//create a whole parser
		check_spaces(argv);
		philo_init(argv);
	}
}
