/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:11:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/14 20:22:38 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *eat(void *arg)
{
	t_mutex mut;
	int		n;

	n = *(int *)arg;
	pthread_mutex_lock(&mut.flag_lock);
	mut.fork[n] = 1;
	printf("Philosopher %d has taken a fork\n", n);
	pthread_mutex_unlock(&mut.flag_lock);
}

void	exec_threads(char **argv)
{
	int     i;
	int     philos;
	t_mutex mut;
	pthread_t thread[ft_atoi(argv[1])];
	
	i = 1;
	mut.fork[ft_atoi(argv[1])];
	philos = ft_atoi(argv[1]);
	pthread_mutex_init(&mut.flag_lock, NULL);
	while (i <= philos)
	{
		int	*a;

		a = (int *)malloc(sizeof(int));
		*a = i;
		if (pthread_create(&thread[i], NULL, &eat, a) != 0)
		{
			perror("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 1;
	while (i <= philos)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("Error\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pthread_attr_destroy(&mut.flag_lock);
}