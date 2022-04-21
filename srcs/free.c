/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:24:44 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/20 10:26:25 by asanthos         ###   ########.fr       */
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
