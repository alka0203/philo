/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:03:49 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 12:04:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		return (1);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->gen->p_eat[philo->i]);
		if ((philo->gen->philo_eat[philo->i]
				<= philo->gen->philo_eat[philo->k])
			&& (philo->gen->philo_eat[philo->i]
				<= philo->gen->philo_eat[philo->j]))
		{
			pthread_mutex_unlock(&philo->gen->p_eat[philo->i]);
			break ;
		}
		pthread_mutex_unlock(&philo->gen->p_eat[philo->i]);
		usleep(50);
	}	
}
