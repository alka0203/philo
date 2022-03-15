/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:11:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/15 14:17:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void    *eat(void *arg)
// {
// 	t_mutex mut;
// 	int		n;

// 	n = *(int *)arg;
// 	pthread_mutex_lock(&mut.flag_lock);
// 	mut.fork[n] = 1;
// 	printf("Philosopher %d has taken a fork\n", n);
// 	pthread_mutex_unlock(&mut.flag_lock);
// 	return (void *)mut.fork;
// }

// void	exec_threads(char **argv)
// {
// 	int     i;
// 	int     philos;
// 	int		*res;
// 	t_mutex mut;
// 	pthread_t thread[ft_atoi(argv[1])];
	
// 	i = 1;
// 	//use x to use the value of i in the function
// 	mut.fork = (int *)malloc(ft_atoi(argv[1]) * sizeof(int));
// 	philos = ft_atoi(argv[1]);
// 	pthread_mutex_init(&mut.flag_lock, NULL);
// 	while (i <= philos)
// 	{
// 		int	*a;

// 		a = (int *)malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(&thread[i], NULL, &eat, a) != 0)
// 		{
// 			perror("Error\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	i = 1;
// 	while (i <= philos)
// 	{
// 		if (pthread_join(thread[i], (void **)&res) != 0)
// 		{
// 			perror("Error\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	printf("%d\n", *res);
// 	pthread_mutex_destroy(&mut.flag_lock);
// }