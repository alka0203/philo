/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:12:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/05 04:07:20 by asanthos         ###   ########.fr       */
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
	i = 0;
	while (i < m_st->args->num_philos)
	{
		m_st->gen->philo_eat[i] = 1;
		i++;
	}
	i = 0;
	while (i < m_st->args->num_philos)
	{
		m_st->gen->num_eat[i] = 1;
		i++;
	}
}

void	init_attr(t_main *m_st, int i)
{
	pthread_mutex_lock(&m_st->gen->mut_init);
	m_st->philo[i].time = m_st->time;
	m_st->philo[i].args = m_st->args;
	m_st->philo[i].i = i;
	if (i == 0)
		m_st->philo[i].k = m_st->args->num_philos - 1;
	else
		m_st->philo[i].k = i - 1;
	if (i == (m_st->args->num_philos - 1))
		m_st->philo[i].j = 0;
	else
		m_st->philo[i].j = i + 1;
	pthread_mutex_unlock(&m_st->gen->mut_init);
}

void	mut_init(t_main *m_st)
{
	int	i;

	i = 0;
	pthread_mutex_init(&m_st->gen->print_mut, NULL);
	pthread_mutex_init(&m_st->gen->ch_flag, NULL);
	pthread_mutex_init(&m_st->gen->tm_t, NULL);
	pthread_mutex_init(&m_st->gen->num, NULL);
	pthread_mutex_init(&m_st->gen->mut_init, NULL);
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_init(&m_st->gen->m_fork[i], NULL);
		pthread_mutex_init(&m_st->gen->eat[i], NULL);
		pthread_mutex_init(&m_st->gen->tm_eat[i], NULL);
		pthread_mutex_init(&m_st->gen->p_eat[i], NULL);
		pthread_mutex_init(&m_st->gen->eat_tm[i], NULL);
		i++;
	}
}

void	mut_dest(t_main *m_st)
{
	int	i;

	i = 0;
	m_st->gen = m_st->philo->gen;
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_destroy(&m_st->gen->eat_tm[i]);
		pthread_mutex_destroy(&m_st->gen->p_eat[i]);
		pthread_mutex_destroy(&m_st->gen->tm_eat[i]);
		pthread_mutex_destroy(&m_st->gen->eat[i]);
		pthread_mutex_destroy(&m_st->gen->m_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&m_st->gen->mut_init);
	pthread_mutex_destroy(&m_st->gen->num);
	pthread_mutex_destroy(&m_st->gen->tm_t);
	pthread_mutex_destroy(&m_st->gen->ch_flag);
	pthread_mutex_destroy(&m_st->gen->print_mut);
}
