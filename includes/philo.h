/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/05 04:11:07 by asanthos         ###   ########.fr       */
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
	int	num_philos;
	int	tm_eat;
	int	tm_die;
	int	tm_sleep;
	int	num_tm_eat;
	int	task_hd;
}	t_args;

typedef struct s_gen
{
	pthread_t		*threads;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*tm_eat;
	pthread_mutex_t	*p_eat;
	pthread_mutex_t	*eat_tm;
	pthread_mutex_t	mut_init;
	pthread_mutex_t	print_mut;
	pthread_mutex_t	num;
	pthread_mutex_t	ch_flag;
	pthread_mutex_t	tm_t;
	int				*fork_st;
	int				*num_eat;
	int				*philo_eat;
	int				*flag2;
	int				flag;
	int				ac;
	char			**av;
}	t_gen;

typedef struct s_time
{
	long int		*tm_eat;
	long int		tm_init;
}	t_time;

/*
i is the philosopher's own id
j is philo + 1's id
k if philo - 1's id
*/
typedef struct s_philo
{
	int				i;
	int				j;
	int				k;
	t_gen			*gen;
	t_time			*time;
	t_args			*args;
}	t_philo;

typedef struct s_main
{
	t_args		*args;
	t_gen		*gen;
	t_time		*time;
	t_philo		*philo;
}	t_main;

//helper functions
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
void		ft_putstr(char *str);
void		*ft_calloc(size_t nmemb, size_t size);
int			check_spaces(char **argv);
int			iter_args(char **argv);

//initialize functions
t_main		*philo_init(char **argv);
void		args_init(t_main *m_st, int argc);
void		time_init(t_main *m_st);
void		struct_init(t_main *m_st, int i);
void		init_attr(t_main *m_st, int i);
void		mut_init(t_main *m_st);
void		mut_dest(t_main *m_st);
void		philo_gen(t_main *m_st);

//time functions
void		time_gen(t_philo *philo);
void		time_tasks(t_philo *philo);
void		check_death(t_philo *philo);
int			check_flag(t_philo *philo);

//sleep functions
void		sleep_func(t_philo *philo);
void		sleep_func2(t_philo *philo);
void		ft_sleep(t_philo *philo, int task_tm);

//num of times eaten functions
void		num_eat(t_philo *philo);
void		philo_eat(t_philo *philo);
int			check_all_eat(t_philo *philo);

//main task functions
void		exec_threads(t_main *m_st);
void		check_fork1(t_philo *philo);
void		free_philo(t_main *m_st);
long int	tm_tasks(t_philo *philo);
void		print_tasks(t_philo *philo);
void		print_t(t_philo *philo, char *s1, char *s2);

//free functions
void		free_mut(t_main *m_st);
void		free_mall(t_main *m_st);
void		eating(t_philo *philo);
int			malloc_protect(t_main *m_st);

#endif
