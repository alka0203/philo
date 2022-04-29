/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:03:27 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 14:08:14 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	args_init(t_main *m_st, int argc)
{
	m_st->args->num_philos = ft_atoi(m_st->gen->av[1]);
	m_st->args->tm_die = ft_atoi(m_st->gen->av[2]);
	m_st->args->tm_eat = ft_atoi(m_st->gen->av[3]);
	m_st->args->tm_sleep = ft_atoi(m_st->gen->av[4]);
	if (argc == 6)
		m_st->args->num_tm_eat = ft_atoi(m_st->gen->av[5]);
}

void	init_main(t_main *m_st, char **argv)
{
	m_st->args = (t_args *)malloc(sizeof(t_args));
	m_st->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	m_st->time = (t_time *)malloc(sizeof(t_time));
	m_st->gen = (t_gen *)malloc(sizeof(t_gen));
	m_st->gen->av = argv;
	m_st->gen->flag = 0;
}

t_main	*philo_init(char **argv)
{
	t_main		*m_st;

	m_st = (t_main *)malloc(sizeof(t_main));
	init_main(m_st, argv);
	m_st->gen->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* ft_atoi(argv[1]));
	m_st->gen->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->mut_colour = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->mut_task = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->tm_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->p_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	m_st->gen->fork_st = ft_calloc(ft_atoi(argv[1]), (sizeof(int)));
	m_st->gen->num_eat = ft_calloc(ft_atoi(argv[1]), (sizeof(int)));
	m_st->gen->philo_eat = ft_calloc(ft_atoi(argv[1]), (sizeof(int)));
	m_st->time->tm_eat = (long int *)malloc(sizeof(long int)
			* ft_atoi(argv[1]));
	m_st->gen->flag2 = ft_calloc(ft_atoi(argv[1]), (sizeof(int)));
	return (m_st);
}
