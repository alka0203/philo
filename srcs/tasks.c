/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:00 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 11:49:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_t(t_philo *philo, char *s1, char *s2)
{
	pthread_mutex_lock(&philo->gen->print_mut);
	if (check_flag(philo) == 1)
		pthread_mutex_unlock(&philo->gen->print_mut);
	else
	{
		printf("%s%ld philo %d %s\n", s1,
			(tm_tasks(philo) - philo->time->tm_init), (philo->i + 1), s2);
		pthread_mutex_unlock(&philo->gen->print_mut);
	}
}

static void	think(t_philo *philo)
{
	print_t(philo, "\e[0;33m", "is thinking");
}

static void	sleep_philo(t_philo *philo)
{
	print_t(philo, "\e[0;95m", "is sleeping");
	ft_sleep(philo, (philo->args->tm_eat + philo->args->tm_sleep));
	think(philo);
}

static void	eating(t_philo *philo)
{
	print_t(philo, "\e[0;31m", "is eating");
	ft_sleep(philo, philo->args->tm_eat);
	pthread_mutex_lock(&philo->gen->ph_eat);
	philo->gen->philo_eat[philo->i] += 1;
	pthread_mutex_unlock(&philo->gen->ph_eat);
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->i] = 0;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
	philo->gen->fork_st[philo->j] = 0;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	if (philo->gen->ac == 6)
	{
		pthread_mutex_lock(&philo->gen->eat[philo->i]);
		philo->gen->num_eat[philo->i] += 1;
		pthread_mutex_unlock(&philo->gen->eat[philo->i]);
		num_eat(philo);
	}
	sleep_philo(philo);
}

static void	check_fork2(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
	if (philo->gen->fork_st[philo->j] == 1)
		sleep_func2(philo);
	philo->gen->fork_st[philo->j] = 1;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	time_gen(philo);
	if (check_flag(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->gen->print_mut);
	printf("\e[0;36m%ld philo %d picks up a fork %d\n",
		(philo->time->tm_eat[philo->i] - philo->time->tm_init),
		(philo->i + 1), (philo->i + 1));
	printf("\e[0;94m%ld philo %d picks up a fork %d\n",
		(philo->time->tm_eat[philo->i] - philo->time->tm_init),
		(philo->i + 1), (philo->j + 1));
	pthread_mutex_unlock(&philo->gen->print_mut);
	eating(philo);
}

int	one_fork(t_philo *philo)
{
	if (philo->args->num_philos == 1)
	{
		printf("\e[0;36m%ld philo %d picks up a fork %d\n",
			(tm_tasks(philo) - philo->time->tm_init),
			(philo->i + 1), (philo->i + 1));
		while (1)
		{
			if (philo->time->tm_eat[philo->i] == 0)
			{
				if (tm_tasks(philo)
					>= (philo->time->tm_init + philo->args->tm_die))
				{
					check_death(philo);
					return (1);
				}
			}
			usleep(1000);
		}
	}
	return (0);
}

void	check_fork1(t_philo *philo)
{
	if (one_fork(philo) == 1)
		return ;
	if ((philo->i % 2 == 0) && (philo->time->tm_eat[philo->i] == 0))
		usleep(1000);
	pthread_mutex_lock(&philo->gen->tm_eat[philo->i]);
	if (philo->time->tm_eat[philo->i] != 0)
	{
		pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
		pthread_mutex_lock(&philo->gen->tm_eat[philo->i]);
		if (tm_tasks(philo)
			>= (philo->time->tm_eat[philo->i] + philo->args->tm_die))
		{
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
			check_death(philo);
			return ;
		}
		else
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
	}
	else
		pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	if (philo->gen->fork_st[philo->i] == 1)
	{
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
		sleep_func(philo);
	}
	else if (philo->gen->fork_st[philo->i] == 0)
	{
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
		pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
		if (philo->gen->fork_st[philo->j] == 1)
		{
			pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
			sleep_func(philo);
		}
		else
			pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	}
	else
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	if (check_flag(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->i] = 1;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	check_fork2(philo);
	if (check_flag(philo) == 1)
		return ;
	philo_eat(philo);
	usleep(1000);
	check_fork1(philo);
}
