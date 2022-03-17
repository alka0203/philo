/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:11:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/17 19:21:35 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(struct timeval *m, t_mutex *mut)
{
	gettimeofday(m, NULL);
	printf("%d philo %d is sleeping\n", m->tv_usec , mut->i);
	usleep(ft_atoi(mut->av[4]));
	gettimeofday(m, NULL);
	printf("%d philo %d is thinking\n", m->tv_usec , mut->i);
}

void    *eat(void *arg)
{
    struct timeval m;
    t_mutex	*mut;

	mut = (t_mutex *)arg;
	if (mut->philo_fork[mut->i] == 1)
	// pthread_mutex_lock(&mut->flag_lock);
	mut->philo_fork[mut->i] = 1;
	gettimeofday(&m, NULL);
	printf("%d philo %d picked up a fork\n", (m.tv_usec - mut->p_create), mut->i);
	mut->j = mut->i - 1;
	mut->k = mut->i + 1;
	if (mut->i == 1)
		mut->j = ft_atoi(mut->av[1]);
	if (mut->i == ft_atoi(mut->av[1]))
		mut->k = 1;
	if (mut->philo_fork[mut->k] == 0)
    {
        pthread_mutex_lock(&mut->sec_lock);
		mut->philo_fork[mut->k] = 1;
		printf("%d philo %d picked up a fork\n", (m.tv_usec - mut->p_create), mut->i);
		printf("%d philo %d is eating\n", (m.tv_usec - mut->p_create), mut->i);
		usleep(ft_atoi(mut->av[3]));
		pthread_mutex_unlock(&mut->sec_lock);
		gettimeofday(&m, NULL);
		mut->tm_a_eat = m.tv_usec;
    }
	else if (mut->philo_fork[mut->j] == 0)
	{
		pthread_mutex_lock(&mut->sec_lock);
		mut->philo_fork[mut->j] = 1;
		printf("%d philo %d picked up a fork\n", (m.tv_usec - mut->p_create), mut->i);
 		printf("%d philo %d is eating\n", (m.tv_usec - mut->p_create), mut->i);
		usleep(ft_atoi(mut->av[3]));
		pthread_mutex_unlock(&mut->sec_lock);
		gettimeofday(&m, NULL);
		mut->tm_a_eat = m.tv_usec;
    }
	// pthread_mutex_unlock(&mut->flag_lock);
	return (void *)mut;
}

void	exec_threads(char **argv)
{
	t_mutex	mut;
    int *res;
    t_args  args;
    pthread_t new[ft_atoi(argv[1])];
    struct timeval m;

	mut.p_create = 0;
	mut.p_create = 0;
	mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(int));
	pthread_mutex_init(&mut.flag_lock, NULL);
    mut.i = 1;
	mut.av = argv;
    args.num_philos = ft_atoi(argv[1]);
	//condition to loop till philo dies
	// while ()
	// {
		while (mut.i <= args.num_philos)
		{
			pthread_mutex_init(&mut.fork[mut.i], NULL);
			gettimeofday(&m, NULL);
			mut.p_create = m.tv_usec;
			if (pthread_create(&new[mut.i], NULL, &eat, &mut) != 0)
				return ;
			pthread_mutex_destroy(&mut.fork[mut.i]);
			mut.i++;
		}
		mut.i = 1;
		while (mut.i <= args.num_philos)
		{
			if (pthread_join(new[mut.i], (void **)&res) != 0)
				return ;
			m = *(struct timeval *)res;
			philo_sleep(&m, &mut);
			mut.i++;
		}
	// }
    pthread_mutex_destroy(&mut.flag_lock);
}
