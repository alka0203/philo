/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:12:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/26 15:39:40 by asanthos         ###   ########.fr       */
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
	pthread_mutex_lock(&m_st->gen->mut_init);
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
	pthread_mutex_unlock(&m_st->gen->mut_init);
}

void	time_tasks(t_philo *philo)
{
	gettimeofday(&philo->time->m, NULL);
	philo->time->tm_tasks = ((philo->time->m.tv_sec * 1000) + (philo->time->m.tv_usec / 1000));
}

long int	tm_tasks(t_philo *philo)
{
	struct timeval	m;
	long int		tasks;

	pthread_mutex_lock(&philo->gen->tm_t);
	gettimeofday(&m, NULL);
	tasks = ((m.tv_sec * 1000) + (m.tv_usec / 1000));
	pthread_mutex_unlock(&philo->gen->tm_t);
	return tasks;
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
	pthread_mutex_init(&m_st->gen->check_eat, NULL);
	pthread_mutex_init(&m_st->gen->pt_mut, NULL);
	pthread_mutex_init(&m_st->gen->ch_flag, NULL);
	pthread_mutex_init(&m_st->gen->tm_t, NULL);
	pthread_mutex_init(&m_st->gen->check_eat, NULL);
	pthread_mutex_init(&m_st->gen->num, NULL);
	pthread_mutex_init(&m_st->gen->lock, NULL);
	pthread_mutex_init(&m_st->gen->n_eat, NULL);
	pthread_mutex_init(&m_st->gen->ph_eat, NULL);
	pthread_mutex_init(&m_st->gen->mut_init, NULL);
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_init(&m_st->gen->m_fork[i], NULL);
		pthread_mutex_init(&m_st->gen->mut_colour[i], NULL);
		pthread_mutex_init(&m_st->gen->mut_task[i], NULL);
		pthread_mutex_init(&m_st->gen->eat[i], NULL);
		pthread_mutex_init(&m_st->gen->tm_eat[i], NULL);
		pthread_mutex_init(&m_st->gen->p_eat[i], NULL);
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

void    mut_dest(t_main *m_st)
{
	int i;

	i = 0;
	// m_st->gen = m_st->philo->gen;
	while (i < m_st->args->num_philos)
	{
		pthread_mutex_destroy(&m_st->gen->p_eat[i]);
		pthread_mutex_destroy(&m_st->gen->tm_eat[i]);
		pthread_mutex_destroy(&m_st->gen->eat[i]);
		pthread_mutex_destroy(&m_st->gen->mut_task[i]);
		pthread_mutex_destroy(&m_st->gen->mut_colour[i]);
		pthread_mutex_destroy(&m_st->gen->m_fork[i]);
		// free(&m_st->gen->m_fork[i]);
		// free(&m_st->gen->threads[i]);
		i++;
	}
	pthread_mutex_destroy(&m_st->gen->mut_init);
	pthread_mutex_destroy(&m_st->gen->ph_eat);
	pthread_mutex_destroy(&m_st->gen->n_eat);
	pthread_mutex_destroy(&m_st->gen->lock);
	pthread_mutex_destroy(&m_st->gen->num);
	pthread_mutex_destroy(&m_st->gen->check_eat);
	pthread_mutex_destroy(&m_st->gen->tm_t);
	pthread_mutex_destroy(&m_st->gen->ch_flag);
	pthread_mutex_destroy(&m_st->gen->pt_mut);
	pthread_mutex_destroy(&m_st->gen->check_eat);
	pthread_mutex_destroy(&m_st->gen->print_mut);
}
