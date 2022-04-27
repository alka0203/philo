/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:24:44 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/27 16:33:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    free_philo(t_main *m_st)
{
    free(m_st->gen);
	free(m_st->args);
	free(m_st->time);
	free(m_st->philo);
}

void	free_mut(t_main *m_st)
{
	free(m_st->gen->p_eat);
	free(m_st->gen->tm_eat);
	free(m_st->gen->eat);
	free(m_st->gen->mut_task);
	free(m_st->gen->mut_colour);
	free(m_st->gen->m_fork);
}

void	free_mall(t_main *m_st)
{
	free(m_st->gen->threads);
	free(m_st->gen->fork_st);
	free(m_st->gen->num_eat);
	free(m_st->gen->philo_eat);
	free(m_st->gen->flag2);
	free(m_st->time->tm_eat);
}
