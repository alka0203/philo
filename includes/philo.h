/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/05 10:41:34 by asanthos         ###   ########.fr       */
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
}   t_gen;

typedef	struct s_time
{
	long int	*tm_eat;
	long int	tm_death;
    long int	tm_init;
}	t_time;

typedef struct s_philo
{
    int             i;
    t_gen           *gen;
    t_time          *time;
}	t_philo;

typedef	struct s_main
{
    t_args          *args;
	t_gen	        *gen;
	t_time	        *time;
	t_philo	        *philo;
}	t_main;

int     ft_atoi(const char *str);
int     ft_isalnum(int c);
void	ft_putstr(char *str);
t_main  *philo_init(char **argv);
void    struct_init(t_main *m_st, int i);
void	*ft_calloc(size_t nmemb, size_t size);
void	check_spaces(char **argv);
void    exec_threads(char **argv, t_main *m_st);
void	check_fork1(t_philo *philo, struct timeval m);
void	check_fork2(t_philo *philo, struct timeval m);
void	eating(t_philo *philo, struct timeval m);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif