/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:11:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/17 00:22:12 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *eat(void *arg)
{
    struct timeval m;
    t_mutex	mut;

	mut = *(t_mutex *)arg;
	mut.philo_fork[mut.i] = 1;
	pthread_mutex_lock(&mut.flag_lock);
	gettimeofday(&m, NULL);
	printf("%ld philo %d picked up a fork\n", m.tv_usec, mut.i);
	if (mut.philo_fork[mut.i + 1] == 0)
		mut.philo_fork[mut.i + 1] = 1;
	else if (mut.philo_fork[mut.i - 1] == 0)
		mut.philo_fork[mut.i - 1] = 1;
	printf("%ld philo %d picked up a fork\n", m.tv_usec, mut.i);
	printf("%ld philo %d is eating\n", m.tv_usec, mut.i);
	pthread_mutex_unlock(&mut.flag_lock);
	return (void *)arg;
}

void	exec_threads(char **argv)
{
	t_mutex	mut;
    int *res;
    t_args  args;
    pthread_t new[ft_atoi(argv[1])];

	mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(int));
	pthread_mutex_init(&mut.flag_lock, NULL);
    mut.i = 1;
    args.num_philos = ft_atoi(argv[1]);
    while (mut.i <= args.num_philos)
    {
        if (pthread_create(&new[mut.i], NULL, &eat, &mut) != 0)
            return ;
        mut.i++;
    }
    mut.i = 1;
    while (mut.i < args.num_philos)
    {
        if (pthread_join(new[mut.i], (void **)&res) != 0)
            return ;
        mut.i++;
    }
    pthread_mutex_destroy(&mut.flag_lock);
}