/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:00 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/06 17:10:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	think(t_philo *philo)
{
	time_tasks(philo);
	printf("\e[0;31m%ld philo %d is thinking\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1));
	think_sleep(philo);
}

static void	sleep_philo(t_philo *philo)
{
	time_tasks(philo);
	printf("\e[0;31m%ld philo %d is sleeping\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1));
	usleep(philo->args->tm_sleep * 1000);
	think(philo);
}

static void	eating(t_philo *philo)
{
	printf("\e[0;31m%ld philo %d is eating\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1));
	usleep(philo->args->tm_eat * 1000);
	philo->gen->fork_st[philo->i] = 0;
	philo->gen->fork_st[philo->j] = 1;
	sleep_philo(philo);
}

static void	check_fork2(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->j] = 1;
	time_gen(philo);
	printf("\e[0;94m%ld philo %d picks up a fork\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	eating(philo);
}

void	check_fork1(t_philo *philo)
{
	if (philo->gen->fork_st[philo->i] == 1)
	{
		philo->gen->flag = 1;
		sleep_func(philo);
	}
	printf("State of flag is: %d\n", philo->gen->flag);
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	printf("first boop\n");
	philo->gen->fork_st[philo->i] = 1;
	time_gen(philo);
	printf("\e[0;36m%ld philo %d picks up a fork\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	check_fork2(philo);
}