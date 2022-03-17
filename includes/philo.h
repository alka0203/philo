/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/17 11:54:24 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_mutex
{
    pthread_mutex_t flag_lock;
    pthread_mutex_t sec_lock;
    pthread_mutex_t *fork;
    int             *philo_fork;
	int				i;
    int             j;
    int             k;
	suseconds_t		p_create;
    suseconds_t     tm_a_eat;
    char            **av;
    
}   t_mutex;

typedef struct s_args
{
    int num_philos;
    int tm_eat;
    int tm_die;
    int tm_sleep;
    int num_tm_eat;
}  t_args;

int     ft_atoi(const char *str);
int     ft_isalnum(int c);
void	exec_threads(char **argv);
void	*ft_calloc(size_t nmemb, size_t size);

#endif