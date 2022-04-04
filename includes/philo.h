/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/04 01:22:15 by asanthos         ###   ########.fr       */
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
	pthread_mutex_t	*m_fork;
    pthread_mutex_t *s_fork;
    pthread_t   	*threads;
    int             *fork_st;
}   t_gen;

typedef	struct s_time
{
	long int	tm_eat;
	long int	tm_death;
    long int	tm_init;
}	t_time;

typedef struct s_philo
{
	pthread_mutex_t *right;
	pthread_mutex_t *left;
    int             i;
    long int        tm_eat;
	long int	    tm_init;
    long int        tm_think;
    t_gen           *gen;
    t_time          *time;
    int             counter;
}	t_philo;

typedef	struct s_main
{
	t_gen	        *gen;
	t_time	        *time;
	t_philo	        *philo;
}	t_main;

int     ft_atoi(const char *str);
int     ft_isalnum(int c);
void	ft_putstr(char *str);
void    philo_init(char **argv);
void    struct_init(t_main *m_st, int i, char **argv);
void	*ft_calloc(size_t nmemb, size_t size);
void	check_spaces(char **argv);
int     exec_threads(char **argv, t_main *m_st);
void	check_fork1(t_philo *philo, struct timeval m);
void	check_fork2(t_philo *philo, struct timeval m);
void	eating(t_philo *philo, struct timeval m);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

#endif