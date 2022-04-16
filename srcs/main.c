/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:13:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/16 13:16:13 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
	t_main	*m_st;

	if (argc == 5 || argc == 6)
	{
		//create a whole parser
		check_spaces(argv);
		m_st = philo_init(argv);
		args_init(m_st, argc);
		exec_threads(m_st);
	}
}
