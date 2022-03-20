/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:40:23 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/19 17:31:31 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_think(t_mutex *mut)
{
	struct timeval	m;

	gettimeofday(&m, NULL);
	printf("%d philo %d is thinking\n", (m.tv_usec - mut->p_create), mut->i);
}

void	philo_sleep(t_mutex	*mut)
{
	struct timeval	m;

	gettimeofday(&m, NULL);
	printf("%d philo %d is sleeping\n", (m.tv_usec - mut->p_create), mut->i);
	usleep(ft_atoi(mut->av[4]));
	philo_think(mut);
}

void    *eat(void *arg)
{
    t_mutex			mut;
    struct timeval	m;

	mut = *(t_mutex *)arg;
	if (mut.flag == 0)
	{
		gettimeofday(&m, NULL);
		mut.p_create = m.tv_usec;
	}
	mut.flag = 1;
	mut.k = mut.i + 1;
	mut.j = mut.i - 1;
	if (mut.i == ft_atoi(mut.av[1]))
		mut.k = 1;
	if (mut.i == 1)
		mut.k = ft_atoi(mut.av[1]);	
	//fork mut.i
	pthread_mutex_lock(&mut.fork[mut.i]);
	gettimeofday(&m, NULL);
	mut.philo_fork[mut.i] = 1;
	printf("%d philo %d picks up a fork\n", (m.tv_usec - mut.p_create), mut.i);
	// pthread_mutex_unlock(&mut.fork[mut.i]);

	//for mut.k
	if (mut.philo_fork[mut.k] == 0 || mut.philo_fork[mut.j] == 0)
	{
		if (mut.philo_fork[mut.k] == 0)
		{
			pthread_mutex_lock(&mut.fork[mut.k]);
			gettimeofday(&m, NULL);
			mut.philo_fork[mut.k] = 1;
			printf("%d philo %d picks up a fork\n", (m.tv_usec - mut.p_create), mut.i);
			pthread_mutex_unlock(&mut.fork[mut.k]);
		}
		else if (mut.philo_fork[mut.j] == 0)
		{
			pthread_mutex_lock(&mut.fork[mut.j]);
			gettimeofday(&m, NULL);
			mut.philo_fork[mut.j] = 1;
			printf("%d philo %d picks up a fork\n", (m.tv_usec - mut.p_create), mut.i);
			pthread_mutex_unlock(&mut.fork[mut.j]);
		}
	}
	// pthread_mutex_unlock(&mut.fork[mut.k]);

	//to eat
	gettimeofday(&m, NULL);
	printf("%d philo %d is eating\n", (m.tv_usec - mut.p_create), mut.i);
	usleep(ft_atoi(mut.av[3]));
	mut.philo_fork[mut.k] = 0;
	mut.philo_fork[mut.i] = 0;
	pthread_mutex_unlock(&mut.fork[mut.i]);
    return arg;
}

void    exec_threads(char **argv)
{
    t_mutex         *mut;
    t_args          *args;
    pthread_t       threads[ft_atoi(argv[1])];

	mut = (t_mutex *)malloc(sizeof(t_mutex));
	mut->flag = 0;
	args = (t_args *)malloc(sizeof(args));
    mut->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    mut->philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(char));
    args->num_philos = ft_atoi(argv[1]);
    mut->av = argv;
    mut->i = 1;
    while (mut->i <= args->num_philos)
    {
        pthread_mutex_init(&mut->fork[mut->i], NULL);
        if (pthread_create(&threads[mut->i], NULL, &eat, mut) != 0)
            return ;
        pthread_mutex_destroy(&mut->fork[mut->i]);
        mut->i++;
    }
    mut->i = 1;
    while (mut->i <= args->num_philos)
    {
        if (pthread_join(threads[mut->i], NULL) != 0)
				  return ;
        mut->i++;
    }
}

