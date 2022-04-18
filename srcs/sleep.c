/* ************************************************************************** */
/*                                                                           */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:26:35 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/10 21:15:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//possible bus error
void	change_val(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->gen->philo_eat[i])
	{
		if (philo->gen->philo_eat[i] == 1)
		{
			usleep(philo->args->tm_eat * 1000);
			change_val(philo);
		}
		i++;
	}
	i = 0;
	while (philo->gen->philo_eat[i])
	{
		philo->gen->philo_eat[i] = 1;
		i++;
	}
}

void	sleep_round(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->gen->philo_eat[i])
	{
		if (philo->gen->philo_eat[i] == 1)
			i++;
		usleep(1000);
	}
}

void	num_eat(t_philo *philo)
{
	if ((philo->gen->num_eat[philo->i] - 1) == philo->args->num_tm_eat)
		philo->gen->flag2[philo->i] = 1;
}

int	check_all_eat(t_philo *philo)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (i < philo->args->num_philos)
	{
		if ((philo->gen->num_eat[philo->i] - 1) == philo->args->num_tm_eat)
			checker += 1;
		i++;
	}
	if (checker == philo->args->num_philos)
		return 1;
	return 0;
}

void	philo_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->gen->philo_eat[philo->i] == 2)
	{
		while (philo->gen->philo_eat[philo->k] == 1 || philo->gen->philo_eat[philo->j] == 1)
			usleep(1000);
	}
	i = 0;
	while (i < philo->args->num_philos)
	{
		// printf("boop\n");
		philo->gen->philo_eat[i] = 1;
		i++;
	}
}

// void	num_eat(t_philo *philo)
// {
// 	if (philo->gen->num_eat[philo->i] == philo->args->num_tm_eat)
// 		return ;
// }

// void	num_eat(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	philo->gen->flag = 1;
// 	while (philo->gen->num_eat[i])
// 	{
// 		if (philo->gen->num_eat[i] != philo->gen->num_eat[i + 1])
// 		{
// 			philo->gen->flag = 0;
// 			break;
// 		}
// 		i++;
// 	}
// }

void	check_death(t_philo *philo)
{
	time_tasks(philo);
	if (philo->time->tm_tasks >= (philo->time->tm_init + philo->args->tm_die))
	{
		printf("\e[1;92m%ld philo %d has died\n", (((philo->time->m.tv_usec / 1000) + (philo->time->m.tv_sec * 1000)) - philo->time->tm_init), (philo->i + 1));
		// philo->gen->flag = 1;
        exit(EXIT_FAILURE);
	}
}

void	sleep_func(t_philo *philo)
{
	pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
	while (philo->gen->fork_st[philo->i] == 1 || philo->gen->fork_st[philo->j] == 1)
	{
		time_tasks(philo);
		if (philo->time->tm_eat[philo->i] == 0)
			check_death(philo);
		usleep(1000);
	}
}

void	sleep_func2(t_philo *philo)
{
	philo->gen->fork_st[philo->i] = 0;
	pthread_mutex_unlock(&philo->gen->lock);
	time_tasks(philo);
	usleep((philo->time->tm_tasks - (philo->time->tm_eat[philo->j] + philo->args->num_tm_eat)) * 1000);
	check_fork1(philo);
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
