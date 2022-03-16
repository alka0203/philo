/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:54:32 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/16 14:07:32 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*eat(void *arg)
{
	struct timeval m;
	int		i;

	i = *(int *)arg;
	// printf("%d\n", mut.philo_fork[0]);
	// pthread_mutex_lock(&mut.fork[i]);
	// mut.philo_fork[i] = 1;
	gettimeofday(&m, NULL);
	printf("%d philo %d picked up a fork\n", m.tv_usec, i);
	//cant start eating without second fork
	//find a way to say which fork;
	// pthread_mutex_unlock(&mut.fork[i]);
	return (void *)arg;
}

void	exec_threads(char **argv)
{
	t_mutex	mut;
	t_args	args;
	int		*a;
	pthread_t thread[3];
	int		i;
	// pthread_mutex_init(mut.fork, NULL);
	i = 1;
	mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(int));
	args.num_philos = ft_atoi(argv[1]);
	mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(int));
	while (i <= args.num_philos)
	{
		a = (int *)malloc(sizeof(int));
		*a = i;
		if (pthread_create(&thread[i], NULL, &eat, a) != 0)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
		// pthread_detach(thread[i]);
		i++;
	}
	i = 1;
	while (i <= args.num_philos)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Error boop");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// pthread_mutex_destroy(mut.fork);
} 
