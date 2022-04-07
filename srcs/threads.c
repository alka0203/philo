/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:09:59 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/07 23:18:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *tasks(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    check_fork1(philo);
    gettimeofday(&philo->time->m, NULL);
    if (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) >= (philo->time->tm_eat[philo->i] + (ft_atoi(philo->gen->av[4]) * 1000)))
	{
		printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
		// philo->gen->flag = 1;
        exit(EXIT_FAILURE);
	}
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
	int *res;

    i = 0;
    while (i < m_st->args->num_philos)
    {
        if (pthread_join(m_st->gen->threads[i], (void **)&res) != 0)
        {
            printf("An error has occurred while joining threads!\n");
            return ;
        }
        if (*res == 1)
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
}
