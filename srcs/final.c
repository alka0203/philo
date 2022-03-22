/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:55:43 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/22 14:34:11 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_fork2(t_mutex *mut)
{
	struct timeval	m;

	if ((mut->philo_fork[mut->i] == 0)
	{
		pthread_mutex_lock(&mut->fork[mut->i]);
		mut->philo_fork[mut->i] = 1;
		gettimeofday(&m, NULL);
		printf("%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - mut->p_create), mut->i);
		pthread_mutex_unlock(&mut->fork[mut->i]);
	}
	else if ((mut->philo_fork[mut->j] == 0)
	{
		pthread_mutex_lock(&mut->fork[mut->i]);
		mut->philo_fork[mut->i]= 1;
		pthread_mutex_unlock(&mut->fork[mut->i]);
	}
	else
	{
		//check which one has lesser seconds
		//sleep for the number of sedonds till philo done eating
		usleep();
	}
}

static void	check_fork1(t_mutex *mut)
{
	struct timeval	m;

	if (mut->philo_fork[mut->i] == 0)
	{
		pthread_mutex_lock(&mut->fork[mut->i]);
		mut->philo_fork[mut->i] = 1;
		gettimeofday(&m, NULL);
		printf("%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - mut->p_create), mut->i);
		pthread_mutex_unlock(&mut->fork[mut->i]);
	}
	else
	{
		//sleep for the number of sedonds till philo done eating
		usleep();
	}
}

void	*tasks(void *args)
{
	t_mutex			*mut;
	struct timeval	m;

	mut = (t_mutex *)args;
	if (mut->flag == 0)
	{
		gettimeofday(&m, NULL);
		mut->p_create = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
		usleep(1000);
	}
	mut->flag = 1;
	mut->k = mut->i + 1;
	mut->j = mut->i - 1;
	if (mut->i == ft_atoi(mut->av[1]))
		mut->k = 1;
	if (mut->i == 1)
		mut->j = ft_atoi(mut->av[1]);
	check_fork1(mut);
	check_fork1(mut);
	return args;
}

static void exec_threads(t_mutex *mut, char **argv, t_args *args)
{
	pthread_t		threads[ft_atoi(argv[1])];
	struct timeval	m;
	
	mut->i = 1;

	mut->tm_eat = 0;
	mut->tm_to_die = 0;
	m.tv_sec = 0;
	m.tv_usec = 0;
	while ((((m.tv_usec / 1000) + (m.tv_sec * 1000)) - mut->tm_eat) <= mut->tm_to_die)
	{
		while (mut->i <= args->num_philos)
		{
			pthread_mutex_init(&mut->fork[mut->i], NULL);
			if (pthread_create(&threads[mut->i], NULL, &tasks, mut) != 0)
				return;
			pthread_mutex_destroy(&mut->fork[mut->i]);
			mut->i++;
		}
		mut->i = 1;
		while (mut->i <= args->num_philos)
		{
			if (pthread_join(threads[mut->i], NULL) != 0)
				return;
			mut->i++;
		}
	}
}

void philo_init(char **argv)
{
	t_mutex *mut;
	t_args *args;

	mut = (t_mutex *)malloc(sizeof(t_mutex));
	args = (t_args *)malloc(sizeof(args));
	mut->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	mut->philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(char));
	args->num_philos = ft_atoi(argv[1]);
	mut->av = argv;
	mut->flag = 0;
	exec_threads(mut, argv, args);
}
