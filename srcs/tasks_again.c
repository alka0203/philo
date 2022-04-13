/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:13:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/11 16:47:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philo.h"


void    check_fork1(t_philo *philo)
{
    if (philo->gen->fork_st[philo->k] == 1 || philo->gen->fork_st[philo->j] == 1)
	{
		time_tasks(philo);
		if (philo->time->tm_eat[philo->i] == 0)
			check_death(philo);
		sleep_func(philo);
	}
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	philo->gen->fork_st[philo->i] = 1;
	time_gen(philo);
	printf("\e[0;36m%ld philo %d picks up a fork %d\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1), (philo->i + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	check_fork2(philo);
}
