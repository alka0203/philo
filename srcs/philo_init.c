/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:03:27 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/04 00:46:11 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"  

// void    struct_init(t_main *m_st, int i, int j, char **argv)
// {
//     m_st->philo[i] = (t_philo *)malloc(sizeof(t_philo));
//     j = i + 1;
//     m_st->philo[i]->i = i + 1;
//     if (i == ft_atoi(argv[1]))
//     {
//         m_st->philo[i]->i = 1;
//         j = 1;
//     }
//     m_st->philo[i]->gen = m_st->gen;
//     m_st->philo[i]->gen->m_fork[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
//     m_st->philo[i]->gen->m_fork[j] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
//     m_st->philo[i]->gen->av = argv;
//     m_st->philo[i]->counter = i;
//     m_st->philo[i]->tm_init = m_st->time->tm_init;
// }

void    philo_init(char **argv)
{
	t_main		*m_st;

	m_st = (t_main *)malloc(sizeof(t_main *));
	m_st->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	m_st->time = (t_time *)malloc(sizeof(t_time));
    m_st->gen = (t_gen *)malloc(sizeof(t_gen));
    m_st->gen->threads = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
    m_st->gen->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	m_st->time->tm_death = ft_atoi(argv[2]);
	m_st->time->tm_eat = 0;
	exec_threads(argv, m_st);
}
