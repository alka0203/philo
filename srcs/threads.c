/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:09:59 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 11:53:19 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*tasks(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->time->tm_eat[philo->i] = 0;
	check_fork1(philo);
	return ((void *)&philo->gen->flag);
}

static void	th_create(t_main *m_st)
{
	int	i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		init_attr(m_st, i);
		if (pthread_create(&m_st->gen->threads[i],
				NULL, &tasks, &m_st->philo[i]) != 0)
		{
			printf("An error has occurred while creating threads!\n");
			return ;
		}
		i++;
	}
}

static void	th_join(t_main *m_st)
{
	int	i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		if (pthread_join(m_st->gen->threads[i], NULL) != 0)
		{
			printf("An error has occurred while joining threads!\n");
			return ;
		}
		i++;
	}
}

void	free_threads(t_main *m_st)
{
	int	i;

	i = 0;
	while (i < m_st->args->num_philos)
	{
		free(&m_st->gen->threads[i]);
		i++;
	}
}

void	exec_threads(t_main *m_st)
{
	time_init(m_st);
	mut_init(m_st);
	philo_gen(m_st);
	th_create(m_st);
	th_join(m_st);
	mut_dest(m_st);
	free_mut(m_st);
	free_mall(m_st);
	free_philo(m_st);
}
