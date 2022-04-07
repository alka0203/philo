/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:00 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/08 02:53:37 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	time_tasks(philo);
	printf("\e[0;33m%ld philo %d is thinking\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1));
}

static void	sleep_philo(t_philo *philo)
{
	time_tasks(philo);
	printf("\e[0;95m%ld philo %d is sleeping\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1));
	usleep(philo->args->tm_sleep * 1000);
	think(philo);
}

static void	eating(t_philo *philo)
{
	time_tasks(philo);
	printf("\e[0;31m%ld philo %d is eating\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1));
	usleep(philo->args->tm_eat * 1000);
	philo->gen->fork_st[philo->i] = 0;
	philo->gen->fork_st[philo->j] = 0;
	sleep_philo(philo);
}

void	check_fork2(t_philo *philo)
{
	if (philo->gen->fork_st[philo->j] == 1)
		sleep_func2(philo);
	pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
	philo->gen->fork_st[philo->j] = 1;
	time_tasks(philo);
	printf("\e[0;94m%ld philo %d picks up a fork %d\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1), (philo->j + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	// pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	eating(philo);
}

void	check_fork1(t_philo *philo)
{
	if (philo->gen->fork_st[philo->k] == 1)
	{
		if ((philo->time->tm_tasks == philo->time->tm_init))
		{
			check_death(philo);
			sleep_func(philo);
		}
		else
			sleep_func(philo);
	}
	// printf("%d\n", philo->gen->fork_st[philo->i]);
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->i] = 1;
	time_gen(philo);
	printf("\e[0;36m%ld philo %d picks up a fork %d\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1), (philo->i + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	check_fork2(philo);
}
