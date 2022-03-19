/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:54:32 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/18 20:41:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*eat(void	*arg)
{
	t_mutex	mut;
	struct timeval m;
	
	return (arg);
}

void    exec_threads(char **argv)
{
    t_mutex         mut;
    t_args          args;
    pthread_t       threads[ft_atoi(argv[1])];
    // struct timeval  m;

    pthread_mutex_init(&mut.my_fork, NULL);
    pthread_mutex_init(&mut.your_fork, NULL);
    mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(char));
    args.num_philos = ft_atoi(argv[1]);
    mut.av = argv;
    mut.i = 1;
    while (mut.i <= args.num_philos)
    {
        if (pthread_create(&(threads[mut.i]), NULL, &eat, NULL) != 0)
				  return ;
        mut.i++;
    }
    mut.i = 1;
    while (mut.i <= args.num_philos)
    {
        if (pthread_join(threads[mut.i], NULL) != 0)
				  return ;
        mut.i++;
    }
    pthread_mutex_destroy(&mut.your_fork);
    pthread_mutex_destroy(&mut.my_fork);
}
