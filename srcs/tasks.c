/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:43:00 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/15 15:23:25 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_tasks(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->print_mut);
	time_tasks(philo);
	printf("%s%ld philo %d %s\n", philo->gen->colour, (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1), philo->gen->task);
	pthread_mutex_unlock(&philo->gen->print_mut);
}

static void	think(t_philo *philo)
{
	philo->gen->colour = "\e[0;33m";
	philo->gen->task = "is thinking";
	print_tasks(philo);
}

static void	sleep_philo(t_philo *philo)
{
	philo->gen->colour = "\e[0;95m";
	philo->gen->task = "is sleeping";
	print_tasks(philo);
	usleep(philo->args->tm_sleep * 1000);
	think(philo);
}

static void	eating(t_philo *philo)
{
	if (philo->gen->fork_st[philo->j] == 1 && philo->gen->fork_st[philo->i] == 1)
	{
		philo->gen->colour = "\e[0;31m";
		philo->gen->task = "is eating";
		print_tasks(philo);
		philo->gen->num_eat[philo->i] += 1;
		usleep(philo->args->tm_eat * 1000);
		pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
		philo->gen->philo_eat[philo->i] = 1;
		philo->gen->fork_st[philo->i] = 0;
		philo->gen->fork_st[philo->j] = 0;
		pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
		sleep_philo(philo);
	}
}

void	check_fork2(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
	philo->gen->fork_st[philo->j] = 1;
	// philo->gen->colour = "\e[0;95m";
	// philo->gen->task = "picks up a fork";
	// print_tasks(philo);
	time_tasks(philo);
	time_gen(philo);
	printf("\e[0;36m%ld philo %d picks up a fork %d\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1), (philo->i + 1));
	printf("\e[0;94m%ld philo %d picks up a fork %d\n", (philo->time->tm_tasks - philo->time->tm_init), (philo->i + 1), (philo->j + 1));
	pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
	eating(philo);
}

void	check_fork1(t_philo *philo)
{
	if (philo->time->tm_eat[philo->i] != 0 )
	{
		time_tasks(philo);
		if (philo->time->tm_tasks >= (philo->time->tm_eat[philo->i] + philo->args->tm_die))
		{
			printf("BOOP\n");
			printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
	pthread_mutex_lock(&philo->gen->lock);
	if (philo->gen->fork_st[philo->i] == 1 || philo->gen->fork_st[philo->j] == 1)
		sleep_func(philo);
	else
		pthread_mutex_unlock(&philo->gen->lock);
	philo->gen->fork_st[philo->i] = 1;
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	check_fork2(philo);
	change_val(philo);
	check_fork1(philo);
}



// void	check_fork1(t_philo *philo)
// {
// 	if (philo->time->tm_eat[philo->i] != 0 )
// 	{
// 		time_tasks(philo);
// 		if (philo->time->tm_tasks >= (philo->time->tm_eat[philo->i] + philo->args->tm_die))
// 		{
// 			printf("BOOP\n");
// 			printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	philo_eat(philo);
// 	pthread_mutex_lock(&philo->gen->lock_both);
// 	pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
// 	pthread_mutex_lock(&philo->gen->lock);
// 	// printf("%d %d\n", philo->gen->fork_st[philo->i], (philo->i + 1));
// 	if (philo->gen->fork_st[philo->i] == 1 || philo->gen->fork_st[philo->j] == 1)
// 		sleep_func(philo);
// 	else
// 		pthread_mutex_unlock(&philo->gen->lock);
// 	philo->gen->fork_st[philo->i] = 1;
// 	time_gen(philo);
// 	printf("\e[0;36m%ld philo %d picks up a fork %d\n", (philo->time->tm_eat[philo->i] - philo->time->tm_init), (philo->i + 1), (philo->i + 1));
// 	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
// 	check_fork2(philo);
// 	change_val(philo);
// 	check_fork1(philo);
// }
