/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:00 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/05 01:55:50 by asanthos         ###   ########.fr       */
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

void	eating(t_philo *philo)
{
	print_t(philo, "\e[0;31m", "is eating");
	ft_sleep(philo, philo->args->tm_eat);
	pthread_mutex_lock(&philo->gen->p_eat[philo->i]);
	philo->gen->philo_eat[philo->i] += 1;
	pthread_mutex_unlock(&philo->gen->p_eat[philo->i]);
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
