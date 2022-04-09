/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:09:59 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/08 18:33:35 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *tasks(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    check_fork1(philo);
    //fork 1 coming out here
    time_tasks(philo);
    if (philo->time->tm_tasks >= (philo->time->tm_eat[philo->i] + philo->args->tm_die))
	{
		printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
		// philo->gen->flag = 1;
        exit(EXIT_FAILURE);
	}
    check_fork1(philo);
    if (philo->gen->flag == 1)
		return (NULL);
    return ((void *)&philo->gen->flag);
}

static void th_create(t_main *m_st)
{
	int	i;

	i = 0;
	while (i < m_st->args->num_philos)
    {
        init_attr(m_st, i);
        if (pthread_create(&m_st->gen->threads[i], NULL, &tasks, &m_st->philo[i]) != 0)
        {
            printf("An error has occurred while creating threads!\n");
            return ;
        }
        i++;
    }
}

static void    th_join(t_main *m_st)
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
        if (m_st->philo[i].gen->flag == 1)
		    return ;
        i++;
    }
}

void    exec_threads(t_main *m_st)
{
    time_init(m_st);
    mut_init(m_st);
	philo_gen(m_st);
    th_create(m_st);
    th_join(m_st);
    mut_dest(m_st);
    if (m_st->philo->gen->flag == 1)
		return ;
}
