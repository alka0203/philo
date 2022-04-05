/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:03:27 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/05 10:42:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"  

void	struct_init(t_main *m_st, int i)
{
	m_st->philo[i].gen = m_st->gen;
	m_st->philo[i].i = i;
	m_st->philo[i].tm_init = m_st->time->tm_init;
	if (i == ft_atoi(m_st->gen->av[1]))
		m_st->philo[i].i = 1;
	else
		m_st->philo[i].i = i + 1;	
}

static t_main	*args_init(char **argv, t_main *m_st)
{
	m_st->args->num_philos = ft_atoi(argv[1]);
	m_st->args->tm_die = ft_atoi(argv[2]);
	m_st->args->tm_eat = ft_atoi(argv[3]);
	m_st->args->tm_sleep = ft_atoi(argv[4]);
	m_st->args->num_tm_eat = ft_atoi(argv[5]);
	return (m_st);
}

t_main    *philo_init(char **argv)
{
	t_main		*m_st;

	m_st = (t_main *)malloc(sizeof(t_main *));
	m_st->args = (t_args *)malloc(sizeof(t_args ));
	m_st->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	m_st->time = (t_time *)malloc(sizeof(t_time));
    m_st->gen = (t_gen *)malloc(sizeof(t_gen));
    m_st->gen->threads = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
    m_st->gen->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	m_st->gen->fork_st = ft_calloc(ft_atoi(argv[1]), sizeof(int));
  	m_st->time->tm_death = ft_atoi(argv[2]);
	m_st->time->tm_eat = 0;
	return(m_st);
}
