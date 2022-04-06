/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:12:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/06 17:04:35 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_attr(t_main *m_st, int i)
{
	// m_st->philo[i].gen = m_st->gen;
	m_st->philo[i].time = m_st->time;
	m_st->philo[i].args = m_st->args;
	m_st->philo[i].i = i;
	if (i == m_st->args->num_philos)
		m_st->philo->j = 0;
	else
		m_st->philo->j = i + 1;
}

void	time_tasks(t_philo *philo)
{
	gettimeofday(&philo->time->m, NULL);
	philo->time->tm_tasks = ((philo->time->m.tv_sec * 1000) + (philo->time->m.tv_usec / 1000));
}

void	time_gen(t_philo *philo)
{
	gettimeofday(&philo->time->m, NULL);
	philo->time->tm_eat[philo->i] = ((philo->time->m.tv_sec * 1000) + (philo->time->m.tv_usec / 1000));
}

void	time_init(t_main *m_st)
{
	gettimeofday(&m_st->time->m, NULL);
	m_st->time->tm_init = ((m_st->time->m.tv_sec * 1000) + (m_st->time->m.tv_usec / 1000));
}

void    mut_init(t_main *m_st)
{
	int i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_init(&m_st->philo->gen->m_fork[i], NULL);
		i++;
	}
}

void    mut_dest(t_main *m_st)
{
	int i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_destroy(&m_st->philo->gen->m_fork[i]);
		i++;
	}
}
