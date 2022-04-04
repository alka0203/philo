/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:06:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/05 00:36:17 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	printf("\e[0;33m%ld philo %d is thinking\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	philo->tm_think = philo->tm_eat + ((ft_atoi(philo->gen->av[2])));
	usleep(philo->tm_think);
}

void	sleeping(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	printf("\e[0;31m%ld philo %d is sleeping\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	usleep(ft_atoi(philo->gen->av[3]));
	thinking(philo);
}

void	eating(t_philo *philo, struct timeval m)
{
	gettimeofday(&m, NULL);
	philo->tm_eat = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
	printf("\e[0;95m%ld philo %d is eating\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	usleep(ft_atoi(philo->gen->av[3]));
	sleeping(philo);
}

void	check_fork2(t_philo *philo, struct timeval m)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->counter]);
    gettimeofday(&m, NULL);
	printf("\e[0;94m%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	pthread_mutex_unlock(&philo->gen->m_fork[philo->counter]);
}

void	check_fork1(t_philo *philo, struct timeval m)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->counter]);
    gettimeofday(&m, NULL);
	printf("\e[0;36m%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	pthread_mutex_unlock(&philo->gen->m_fork[philo->counter]);
}

//problem is philosophers going one at a time aint knowing that it's locked.
