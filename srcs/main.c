/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:13:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/04 13:12:32 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_main	*m_st;

	if (argc == 5)
	{
		//create a whole parser
		check_spaces(argv);
		m_st = philo_init(argv);
		exec_threads(argv, m_st);
	}
}
