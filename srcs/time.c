/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:59:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/05 04:08:45 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	tm_tasks(t_philo *philo)
{
	struct timeval	m;
	long int		tasks;

	pthread_mutex_lock(&philo->gen->tm_t);
	gettimeofday(&m, NULL);
	tasks = ((m.tv_sec * 1000) + (m.tv_usec / 1000));
	pthread_mutex_unlock(&philo->gen->tm_t);
	return (tasks);
}

void	time_gen(t_philo *philo)
{
	struct timeval	m;

	gettimeofday(&m, NULL);
	pthread_mutex_lock(&philo->gen->eat_tm[philo->i]);
	philo->time->tm_eat[philo->i] = ((m.tv_sec * 1000)
			+ (m.tv_usec / 1000));
	pthread_mutex_unlock(&philo->gen->eat_tm[philo->i]);
}

void	time_init(t_main *m_st)
{
	struct timeval	m;

	gettimeofday(&m, NULL);
	m_st->time->tm_init = ((m.tv_sec * 1000) + (m.tv_usec / 1000));
}
