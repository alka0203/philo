/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:26:35 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/10 21:15:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_sleep(t_philo *philo, int task_tm)
{
	struct timeval	m;
	long int		eat;

	gettimeofday(&m, NULL);
	pthread_mutex_lock(&philo->gen->eat_tm[philo->i]);
	eat = philo->time->tm_eat[philo->i];
	pthread_mutex_unlock(&philo->gen->eat_tm[philo->i]);
	while ((eat + task_tm)
			> ((m.tv_sec * 1000) + (m.tv_usec / 1000)))
	{
		gettimeofday(&m, NULL);
		usleep(500);
	}
}

int	check_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	if (philo->gen->fork_st[philo->i] == 0)
	{
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
		pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
		if (philo->gen->fork_st[philo->j] == 0)
		{
			pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	}
	else
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	return (0);
}

void	sleep_func(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->gen->tm_eat[philo->i]);
		if (philo->time->tm_eat[philo->i] == 0)
		{
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
			if (tm_tasks(philo) >= (philo->time->tm_init + philo->args->tm_die))
			{
				check_death(philo);
				break ;
			}
		}
		else
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
		if (check_sleep(philo) == 1)
			break ;
		usleep(150);
	}
}

void	sleep_func2(t_philo *philo)
{
	long int	eat;

	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->i] = 0;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	eat = philo->time->tm_eat[philo->j];
	while (1)
	{
		if (tm_tasks(philo)
			== (eat + philo->args->num_tm_eat))
			break ;
		usleep(50);
	}
	check_fork1(philo);
}
