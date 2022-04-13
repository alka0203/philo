/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:12:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/11 15:09:33 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_gen(t_main *m_st)
{
	int	i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		m_st->philo[i].gen = m_st->gen;
		i++;
	}
}

void	init_attr(t_main *m_st, int i)
{
	m_st->philo[i].time = m_st->time;
	m_st->philo[i].args = m_st->args;
	m_st->philo[i].i = i;
	if(i == 0)
		m_st->philo[i].k = m_st->args->num_philos - 1;
	else
		m_st->philo[i].k = i - 1;
	if (i == (m_st->args->num_philos - 1))
		m_st->philo[i].j = 0;
	else
		m_st->philo[i].j = i + 1;
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
	pthread_mutex_init(&m_st->gen->print_mut, NULL);
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_init(&m_st->gen->m_fork[i], NULL);
		i++;
	}
}

void    mut_dest(t_main *m_st)
{
	int i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_destroy(&m_st->gen->m_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&m_st->gen->print_mut);
}
