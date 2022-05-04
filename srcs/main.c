/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:13:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/05 03:42:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_main	*m_st;

	if (argc == 5 || argc == 6)
	{
		if (iter_args(argv) == 1 || check_spaces(argv) == 1)
			return (1);
		m_st = philo_init(argv);
		if (malloc_protect(m_st) == 1)
			return (0);
		m_st->gen->ac = argc;
		args_init(m_st, argc);
		exec_threads(m_st);
		free(m_st);
	}
	else
		printf("Wrong number of arguments sir!\n");
	return (0);
}
