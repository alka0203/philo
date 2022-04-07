/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:26:35 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/08 02:53:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_death(t_philo *philo)
{
	time_gen(philo);
	if (philo->time->tm_tasks >= (philo->time->tm_init + philo->args->tm_die))
	{
		printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
		// philo->gen->flag = 1;
        exit(EXIT_FAILURE);
	}
}

void	sleep_func(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		check_fork1(philo);
	}
}

void	sleep_func2(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		check_fork2(philo);
	}
}

void    think_sleep(t_philo *philo)
{
    long int    die_tm;
    while (1)
    {
        usleep(1000);
        gettimeofday(&philo->time->m, NULL);
        die_tm = ((philo->time->m.tv_sec * 1000) + (philo->time->m.tv_usec / 1000)) - philo->time->tm_eat[philo->i];
        if ((die_tm + 1) == philo->args->tm_die)
            break;
    }
}
