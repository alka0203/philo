/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/06 15:42:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_args
{
    int num_philos;
    int tm_eat;
    int tm_die;
    int tm_sleep;
    int num_tm_eat;
}  t_args;

typedef struct s_gen
{
    char            **av;
    int             *fork_st;
	pthread_mutex_t	*m_fork;
    pthread_mutex_t eat;
    pthread_mutex_t sleep;
    pthread_mutex_t think;
    pthread_t   	*threads;
    int             flag;
}   t_gen;

typedef	struct s_time
{
    struct timeval  m;
	long int	    *tm_eat;
	long int	    tm_death;
    long int	    tm_init;
    long int        tm_gen;
    long int        tm_left;
    long int        tm_tasks;
}	t_time;

typedef struct s_philo
{
    int             i;
    int             j;
    t_gen           *gen;
    t_time          *time;
    t_args          *args;
}	t_philo;

typedef	struct s_main
{
    t_args          *args;
//	t_gen	        *gen;
	t_time	        *time;
	t_philo	        *philo;
}	t_main;

int     ft_atoi(const char *str);
int     ft_isalnum(int c);
void	ft_putstr(char *str);
t_main	*philo_init(char **argv);
void	args_init(t_main *m_st);
void	time_init(t_main *m_st);
void	time_gen(t_philo *philo);
void	time_tasks(t_philo *philo);
void    struct_init(t_main *m_st, int i);
void	init_attr(t_main *m_st, int i);
void	*ft_calloc(size_t nmemb, size_t size);
void	check_spaces(char **argv);
void    exec_threads(t_main *m_st);
void	check_fork1(t_philo *philo);
void    mut_init(t_main *m_st);
void    mut_dest(t_main *m_st);
void	sleep_func(t_philo *philo);
void    think_sleep(t_philo *philo);

#endif