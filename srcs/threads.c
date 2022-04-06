/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:09:59 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/06 17:34:59 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *tasks(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    check_fork1(philo);
    return (philo);
}

void    exec_threads(t_main *m_st)
{
    int i;
    pthread_t   *threads;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * m_st->args->num_philos);
    time_init(m_st);
    mut_init(m_st);
    printf("Before creation\n");
    i = 0;
    while (i < m_st->args->num_philos)
    {
        m_st->philo[i].gen = m_st->philo[i].gen;
        init_attr(m_st, i);
        if (pthread_create(&threads[i], NULL, &tasks, &m_st->philo[i]) != 0)
        {
            printf("An error has occurred while creating threads!\n");
            return ;
        }
        i++;
    }
    printf("After join!\n");
    i = 0;
    while (i < m_st->args->num_philos)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            printf("An error has occurred while joining threads!\n");
            return ;
        }
        printf("lala\n");
        i++;
    }
    mut_dest(m_st);
}
