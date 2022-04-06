/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:03:27 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/06 15:43:27 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	args_init(t_main *m_st)
{
	m_st->args->num_philos = ft_atoi(m_st->philo->gen->av[1]);
	m_st->args->tm_die = ft_atoi(m_st->philo->gen->av[2]);
	m_st->args->tm_eat = ft_atoi(m_st->philo->gen->av[3]);
	m_st->args->tm_sleep = ft_atoi(m_st->philo->gen->av[4]);
	// m_st->args->num_tm_eat = ft_atoi(argv[5]);
}

t_main	*philo_init(char **argv)
{
	t_main		*m_st;

	m_st = (t_main *)malloc(sizeof(t_main));
	m_st->args = (t_args *)malloc(sizeof(t_args));
	m_st->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	m_st->time = (t_time *)malloc(sizeof(t_time));
    m_st->philo->gen = (t_gen *)malloc(sizeof(t_gen));
	m_st->philo->gen->av = argv;
    m_st->philo->gen->threads = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
    m_st->philo->gen->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (ft_atoi(argv[1])));
	m_st->philo->gen->fork_st = ft_calloc(ft_atoi(argv[1]), (sizeof(int)));
	m_st->time->tm_eat = (long int *)malloc(sizeof(long int) * ft_atoi(argv[1]));
	m_st->philo->gen->flag = 0;
	return (m_st);
}
