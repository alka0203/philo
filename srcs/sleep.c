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

int	check_flag(t_philo *philo)
{
	if (philo->gen->ac == 6)
	{
		pthread_mutex_lock(&philo->gen->ch_flag);
		if (philo->gen->flag == 1)
		{
			pthread_mutex_unlock(&philo->gen->ch_flag);
			return 1;
		}
		else if (philo->gen->flag == 0)
		{
			pthread_mutex_unlock(&philo->gen->ch_flag);
			if (check_all_eat(philo) == 1)
				return 1;
		}
		else
			pthread_mutex_unlock(&philo->gen->ch_flag);
	}
	else
	{
		pthread_mutex_lock(&philo->gen->ch_flag);
		if (philo->gen->flag == 1)
		{
			pthread_mutex_unlock(&philo->gen->ch_flag);
			return 1;
		}
		else
			pthread_mutex_unlock(&philo->gen->ch_flag);
	}
	return 0;
}

void	ft_sleep2(t_philo *philo)
{
	struct timeval	m;

	while (42)
	{
		gettimeofday(&m, NULL);
		//change depending on task
		if (philo->time->tm_eat[philo->i] + philo->args->tm_eat + philo->args->tm_sleep == ((m.tv_sec * 1000) + (m.tv_usec / 1000)))
			break;
		usleep(500);
	}
}

void	ft_sleep(t_philo *philo, int task_tm)
{
	struct timeval	m;

	while (42)
	{
		gettimeofday(&m, NULL);
		//change depending on task
		if (philo->time->tm_eat[philo->i] + task_tm == ((m.tv_sec * 1000) + (m.tv_usec / 1000)))
			break;
		usleep(500);
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
	int	x;

	pthread_mutex_lock(&philo->gen->eat[philo->i]);
	x = philo->gen->num_eat[philo->i];
	pthread_mutex_unlock(&philo->gen->eat[philo->i]);
	if ((x - 1) == philo->args->num_tm_eat)
	{
		pthread_mutex_lock(&philo->gen->num);
		philo->gen->flag2[philo->i] = 1;
		pthread_mutex_unlock(&philo->gen->num);
	}
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
	while (1)
	{
		pthread_mutex_lock(&philo->gen->p_eat[philo->i]);
		if ((philo->gen->philo_eat[philo->i] <= philo->gen->philo_eat[philo->k]) && (philo->gen->philo_eat[philo->i] <= philo->gen->philo_eat[philo->j]))
		{
			pthread_mutex_unlock(&philo->gen->p_eat[philo->i]);
			break;
		}
		pthread_mutex_unlock(&philo->gen->p_eat[philo->i]);
		usleep(50);
	}	
}

void	check_death(t_philo *philo)
{
	print_t(philo, "\e[1;92m", "has died");
	pthread_mutex_lock(&philo->gen->ch_flag);
	philo->gen->flag = 1;
	pthread_mutex_unlock(&philo->gen->ch_flag);
}

void	sleep_func(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->gen->tm_eat[philo->i]);
		if (philo->time->tm_eat[philo->i] == 0)
		{
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
			if (tm_tasks(philo) >= (philo->time->tm_init + philo->args->tm_die))
			{
				check_death(philo);
				break;
			}
		}
		else
			pthread_mutex_unlock(&philo->gen->tm_eat[philo->i]);
		pthread_mutex_lock(&philo->gen->m_fork[philo->i]);
		if (philo->gen->fork_st[philo->i] == 0)
		{
			pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
			pthread_mutex_lock(&philo->gen->m_fork[philo->j]);
			if (philo->gen->fork_st[philo->j] == 0)
			{
				pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
				break;
			}
			else
				pthread_mutex_unlock(&philo->gen->m_fork[philo->j]);
		}
		else
			pthread_mutex_unlock(&philo->gen->m_fork[philo->i]);
		usleep(50);
	}
}

void	sleep_func2(t_philo *philo)
{
	philo->gen->fork_st[philo->i] = 0;
	pthread_mutex_unlock(&philo->gen->lock);
	while (1)
	{
		if (tm_tasks(philo) == (philo->time->tm_eat[philo->j] + philo->args->num_tm_eat))
			break;
		usleep(50);
	}
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
