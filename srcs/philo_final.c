/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_final.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:34:29 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/02 20:44:19 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinking(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	printf("%ld philo %d is thinking\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	philo->tm_think = philo->tm_eat + ((ft_atoi(philo->gen->av[2])) * 1000);
	usleep(philo->tm_think * 1000);
}

void	sleeping(t_philo *philo)
{
	struct timeval m;

	gettimeofday(&m, NULL);
	printf("%ld philo %d is sleeping\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
	usleep(ft_atoi(philo->gen->av[3]) * 1000);
	thinking(philo);
}

void	eating(t_philo *philo, struct timeval m)
{
	if (philo->gen->fork_st[philo->counter] == 1 && philo->gen->fork_st[philo->counter + 1] == 1)
	{
		philo->tm_eat = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
		printf("%ld philo %d is eating\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
		usleep(ft_atoi(philo->gen->av[3]) * 1000);
		philo->gen->fork_st[philo->counter] = 0;
		philo->gen->fork_st[philo->counter + 1] = 0;
		sleeping(philo);
	}
}

void	check_fork2(t_philo *philo, struct timeval m)
{
	if (philo->gen->fork_st[philo->counter + 1] == 0)
	{
		pthread_mutex_lock(philo->gen->m_fork);
		philo->gen->fork_st[philo->counter + 1] = 1;
		printf("%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
		pthread_mutex_unlock(philo->gen->m_fork);
	}
	else if (philo->gen->fork_st[philo->counter + 1] == 1)
	{
		//change
		usleep(2000);
	}
}

void	check_fork1(t_philo *philo, struct timeval m)
{
	if (philo->counter == 2)
		printf("%d\n", philo->gen->fork_st[philo->counter]);
	if (philo->gen->fork_st[philo->counter] == 0)
	{
		pthread_mutex_lock(philo->gen->m_fork);
		philo->gen->fork_st[philo->counter] = 1;
		printf("%ld philo %d picks up a fork\n", (((m.tv_usec / 1000) + (m.tv_sec * 1000)) - philo->tm_init), philo->counter);
		pthread_mutex_unlock(philo->gen->m_fork);
	}
	else if (philo->gen->fork_st[philo->counter] == 1)
	{
		//change
		usleep(2000);
	}
}

void	*tasks(void *arg)
{
	t_philo	*philo;
	struct timeval m;

	philo = (t_philo *)arg;
	gettimeofday(&m, NULL);
	check_fork1(philo, m);
	check_fork2(philo, m);
	eating(philo, m);
	return (arg);
}

int	exec_threads(char **argv, t_main *m_st)
{
	int	i;
	int	*res;
	struct timeval m;

	i = 1;
	gettimeofday(&m, NULL);
	m_st->time->tm_init = ((m.tv_usec / 1000) + (m.tv_sec * 1000));
	while (i <= ft_atoi(argv[1]))
	{
		pthread_mutex_init(&m_st->philo[i]->gen->m_fork[i], NULL);
		m_st->philo[i]->gen->av = argv;
        m_st->philo[i]->i = i;
		m_st->philo[i]->counter = i;
		m_st->philo[i]->tm_init = m_st->time->tm_init;
		if (pthread_create(&m_st->philo[i]->gen->threads[i], NULL, &tasks, m_st->philo[i]) != 0)
		{
			printf("An error has occurred while creating threads!\n");
			exit(EXIT_FAILURE);
		}
		pthread_mutex_destroy(&m_st->philo[i]->gen->m_fork[i]);
		usleep(1000);
		i++;
	}
    while (i <= ft_atoi(argv[1]))
    {
        i = 1;
        //return tm_eat value
        if (pthread_join(m_st->philo[i]->gen->threads[i], (void **)&res) != 0)
        {
            printf("An error has occurred while joininG threads!\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
	return (i);
}

void    philo_init(char **argv)
{
	t_main			*m_st;
	struct timeval	death;
	int         i;

	m_st = (t_main *)malloc(sizeof(t_main *));
	m_st->philo = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	m_st->time = (t_time *)malloc(sizeof(t_time));
	m_st->time->tm_death = ft_atoi(argv[2]);
	m_st->time->tm_eat = 0;
    i = 1;
	while (i <= ft_atoi(argv[1]))
	{
		m_st->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		m_st->philo[i]->gen = (t_gen *)malloc(sizeof(t_gen));
		m_st->philo[i]->gen->threads = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		m_st->philo[i]->gen->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		m_st->philo[i]->gen->fork_st = ft_calloc(ft_atoi(argv[1]), sizeof(int *));
		i++;
	}
	i = exec_threads(argv, m_st);
	gettimeofday(&death, NULL);
	printf("%ld philo %d has died\n", ((death.tv_sec * 1000) + death.tv_usec / 1000), i);
}
