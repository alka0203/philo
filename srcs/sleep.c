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

	while (42)
	{
		gettimeofday(&m, NULL);
		pthread_mutex_lock(&philo->gen->time_task);
		if (philo->time->tm_eat[philo->i] + task_tm
			== ((m.tv_sec * 1000) + (m.tv_usec / 1000)))
		{
			pthread_mutex_unlock(&philo->gen->time_task);
			break ;
		}
		pthread_mutex_unlock(&philo->gen->time_task);
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
	philo->gen->fork_st[philo->i] = 0;
	pthread_mutex_unlock(&philo->gen->lock);
	while (1)
	{
		if (tm_tasks(philo) == (philo->time->tm_eat[philo->j]
					+ philo->args->num_tm_eat))
			break ;
		usleep(50);
	}
	check_fork1(philo);
}
