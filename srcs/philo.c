/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:49:01 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/04 15:25:24 by asanthos         ###   ########.fr       */
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

static void	mut_init(t_main *m_st, char **argv)
{
	int	i;

	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_init(&m_st->gen->m_fork[i], NULL);
		i++;
	}
}

static void	mut_dest(t_main *m_st, char **argv)
{
	int	i;

	i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&m_st->gen->m_fork[i]);
		i++;
	}
}

void	exec_threads(char **argv, t_main *m_st)
{
	struct timeval	m;
	int				*res;
	int				i;
	int				j;

	i = 1;
	j = 0;
	gettimeofday(&m, NULL);
	m_st->time->tm_init = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
	mut_init(m_st, argv);
	printf("boop\n");
	while (i <= ft_atoi(m_st->gen->av[1]))
	{
		if (i == ft_atoi(argv[1]))
			j = 1;
		else
			j = i + 1;
		struct_init(m_st, i);
		if (pthread_create(&m_st->philo[i].gen->threads[i], NULL, &tasks, &m_st->philo[i]) != 0)
		{
			printf("An error has occurred while creating threads!\n");
			return ;
		}
		i++;
	}
	i = 1;
    while (i <= ft_atoi(argv[1]))
    {
        if (pthread_join(m_st->philo[i].gen->threads[i], (void **)&res) != 0)
        {
            printf("An error has occurred while joining threads!\n");
            return ;
		
        }
		// pthread_mutex_destroy(&m_st->philo[i].gen->m_fork[j]);
		// pthread_mutex_destroy(&m_st->philo[i].gen->m_fork[i]);
        i++;
    }
	mut_dest(m_st, argv);
}
