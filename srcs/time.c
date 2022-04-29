/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 11:59:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 12:02:39 by asanthos         ###   ########.fr       */
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
	gettimeofday(&philo->time->m, NULL);
	philo->time->tm_eat[philo->i] = ((philo->time->m.tv_sec * 1000)
			+ (philo->time->m.tv_usec / 1000));
}

void	time_init(t_main *m_st)
{
	gettimeofday(&m_st->time->m, NULL);
	m_st->time->tm_init = ((m_st->time->m.tv_sec * 1000)
			+ (m_st->time->m.tv_usec / 1000));
}

void	check_death(t_philo *philo)
{
	print_t(philo, "\e[1;92m", "has died");
	pthread_mutex_lock(&philo->gen->ch_flag);
	philo->gen->flag = 1;
	pthread_mutex_unlock(&philo->gen->ch_flag);
}
