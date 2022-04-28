/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:13:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/28 15:53:41 by asanthos         ###   ########.fr       */
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
		if (check_args(argv) == 1 || iter_args(argv) == 1)
			return 1;
		m_st = philo_init(argv);
		m_st->gen->ac = argc;
		args_init(m_st, argc);
		exec_threads(m_st);
		free(m_st);
	}
}
