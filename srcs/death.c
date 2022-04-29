/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:52:29 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/29 12:52:54 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_death(t_philo *philo)
{
	print_t(philo, "\e[1;92m", "has died");
	pthread_mutex_lock(&philo->gen->ch_flag);
	philo->gen->flag = 1;
	pthread_mutex_unlock(&philo->gen->ch_flag);
}

int	flag_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->gen->ch_flag);
	if (philo->gen->flag == 1)
	{
		pthread_mutex_unlock(&philo->gen->ch_flag);
		return (1);
	}
	else if (philo->gen->flag == 0)
	{
		pthread_mutex_unlock(&philo->gen->ch_flag);
		if (check_all_eat(philo) == 1)
			return (1);
	}
	else
		pthread_mutex_unlock(&philo->gen->ch_flag);
	return (0);
}

int	check_flag(t_philo *philo)
{
	if (philo->gen->ac == 6)
	{
		if (flag_eat(philo) == 1)
			return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->gen->ch_flag);
		if (philo->gen->flag == 1)
		{
			pthread_mutex_unlock(&philo->gen->ch_flag);
			return (1);
		}
		else
			pthread_mutex_unlock(&philo->gen->ch_flag);
	}
	return (0);
}
