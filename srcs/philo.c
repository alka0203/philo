/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:49:01 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/05 00:36:23 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*tasks(void *arg)
{
	t_philo	*philo;
	struct timeval m;

	philo = (t_philo *)arg;
	gettimeofday(&m, NULL);
	check_fork1(philo, m);
	check_fork2(philo, m);
	eating(philo, m);
	gettimeofday(&m, NULL);
	if (((m.tv_usec / 1000) + (m.tv_sec * 1000)) >= (philo->tm_eat + ft_atoi(philo->gen->av[4])))
	{
		printf("\e[1;92m%ld philo %d has died\n", ((m.tv_usec / 1000) + (m.tv_sec * 1000)), philo->counter);
		return (NULL);
	}
	return (arg);
}

void	struct_init(t_main *m_st, int i, char **argv)
{
	m_st->philo[i].gen = m_st->gen;
	m_st->philo[i].gen->av = argv;
	m_st->philo[i].counter = i;
	m_st->philo[i].tm_init = m_st->time->tm_init;
}

int	exec_threads(char **argv, t_main *m_st)
{
	int	i;
	int	j;

	int	*res;
	struct timeval m;

	i = 1;
	j = 0;
	gettimeofday(&m, NULL);
	m_st->time->tm_init = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
	while (i <= ft_atoi(argv[1]))
	{
		j = i + 1;
		m_st->philo[i].i = i + 1;
		if (i == ft_atoi(argv[1]))
		{
			m_st->philo[i].i = 1;
			j = 1;
		}
		struct_init(m_st, i, argv);
		pthread_mutex_init(&m_st->philo[i].gen->m_fork[j], NULL);
		pthread_mutex_init(&m_st->philo[i].gen->m_fork[i], NULL);
		if (pthread_create(&m_st->philo[i].gen->threads[i], NULL, &tasks, &m_st->philo[i]) != 0)
		{
			printf("An error has occurred while creating threads!\n");
			return (0);
		}
		pthread_mutex_destroy(&m_st->philo[i].gen->m_fork[j]);
		pthread_mutex_destroy(&m_st->philo[i].gen->m_fork[i]);
		i++;
	}
    while (i <= ft_atoi(argv[1]))
    {
        i = 1;
        //return tm_eat value
        if (pthread_join(m_st->philo[i].gen->threads[i], (void **)&res) != 0)
        {
            printf("An error has occurred while joininG threads!\n");
            return (0);
        }
        i++;
    }
	return (i);
}
