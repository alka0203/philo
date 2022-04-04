/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:06:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/04 15:42:01 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	pthread_mutex_lock(&philo->gen->think);
	printf("\e[0;33m%ld philo %d is thinking\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	philo->tm_think = philo->tm_eat + ((ft_atoi(philo->gen->av[2])));
	pthread_mutex_unlock(&philo->gen->think);
	usleep(philo->tm_think);
}

void	sleeping(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	pthread_mutex_lock(&philo->gen->sleep);
	printf("\e[0;31m%ld philo %d is sleeping\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	pthread_mutex_unlock(&philo->gen->sleep);
	usleep(ft_atoi(philo->gen->av[3]));
	thinking(philo);
}

void	eating(t_philo *philo, struct timeval m)
{
	gettimeofday(&m, NULL);
	philo->tm_eat = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
	pthread_mutex_lock(&philo->gen->eat);
	printf("\e[0;95m%ld philo %d is eating\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	pthread_mutex_unlock(&philo->gen->eat);
	usleep(ft_atoi(philo->gen->av[3]) * 1000);
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	pthread_mutex_unlock(&philo->gen->m_fork[philo->counter]);
	sleeping(philo);
}

void	check_fork2(t_philo *philo, struct timeval m)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
    gettimeofday(&m, NULL);
	printf("\e[0;94m%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
}

void	check_fork1(t_philo *philo, struct timeval m)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->counter]);
    gettimeofday(&m, NULL);
	printf("\e[0;36m%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
}

//problem is philosophers going one at a time aint knowing that it's locked.
