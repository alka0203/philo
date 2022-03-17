/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:54:32 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/17 19:45:29 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *eat
{
    
}

void    exec_threads(char **argv)
{
    t_mutex         mut;
    t_args          args;
    pthread_t       threads[ft_atoi(argv][1])];
    struct timeval  m;

    pthread_mutex_init(&mut.flag_lock, NULL);
    mut.philo_fork = ft_calloc(ft_atoi(argv[1]), sizeof(char));
    args.num_philos = ft_atoi();
    pthread_mutex_destroy(&mut.flag_lock);
}
