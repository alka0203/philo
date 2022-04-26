 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:13:34 by asanthos          #+#    #+#             */
/*   Updated: 2022/04/10 16:14:29 by asanthos         ###   ########.fr       */
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
    int task_hd;
}  t_args;

typedef struct s_gen
{
    char            **av;
    int             ac;
    int             *fork_st;
	pthread_mutex_t	*m_fork;
    pthread_mutex_t print_mut;
    pthread_mutex_t pt_mut;
    pthread_mutex_t lock;
    pthread_mutex_t lock_both;
    pthread_mutex_t num;
    pthread_mutex_t check_eat;
    pthread_mutex_t ch_flag;
    pthread_mutex_t tm_t;
    pthread_mutex_t *mut_colour;
    pthread_mutex_t *mut_task;
    pthread_mutex_t *eat;
    pthread_mutex_t *tm_eat;
    pthread_mutex_t ph_eat;
    pthread_mutex_t *p_eat;
    pthread_mutex_t n_eat;
    pthread_mutex_t mut_init;
    pthread_t   	*threads;
    int             *num_eat;
    int             *philo_eat;
	char			*colour;
	char			*task;
    int             flag;
    int             *flag2;
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
    int             k;
    t_gen           *gen;
    t_time          *time;
    t_args          *args;
}	t_philo;

typedef	struct s_main
{
    t_args          *args;
	t_gen	        *gen;
	t_time	        *time;
	t_philo	        *philo;
}	t_main;

// int         ft_atoi(const char *str);
// int         ft_isalnum(int c);
// void    	ft_putstr(char *str);
// t_main  	*philo_init(char **argv);
// void    	args_init(t_main *m_st, int argc);
// void    	time_init(t_main *m_st);
// void    	time_gen(t_philo *philo);
// void		time_tasks(t_philo *philo);
// void		struct_init(t_main *m_st, int i);
// void		init_attr(t_main *m_st, int i);
// void		*ft_calloc(size_t nmemb, size_t size);
// void		check_spaces(char **argv);
// void		exec_threads(t_main *m_st);
// void		check_fork1(t_philo *philo);
// void		mut_init(t_main *m_st);
// void		mut_dest(t_main *m_st);
// void		sleep_func(t_philo *philo);
// void	    sleep_func2(t_philo *philo);
// void		think_sleep(t_philo *philo);
// void		philo_gen(t_main *m_st);
// void		check_death(t_philo *philo);
// void		num_eat(t_philo *philo);
// void		philo_eat(t_philo *philo);
// void		sleep_round(t_philo *philo);
// void	    change_val(t_philo *philo);
// int			check_all_eat(t_philo *philo);
// void        free_philo(t_main *m_st);
// void        ft_sleep(t_philo *philo);
// void	    print_t(t_philo *philo, char *s1, char *s2);

int         ft_atoi(const char *str);
int         ft_isalnum(int c);
void    	ft_putstr(char *str);
t_main  	*philo_init(char **argv);
void    	args_init(t_main *m_st, int argc);
void    	time_init(t_main *m_st);
void    	time_gen(t_philo *philo);
void		time_tasks(t_philo *philo);
void		struct_init(t_main *m_st, int i);
void		init_attr(t_main *m_st, int i);
void		*ft_calloc(size_t nmemb, size_t size);
void		check_spaces(char **argv);
void		exec_threads(t_main *m_st);
void		check_fork1(t_philo *philo);
void		mut_init(t_main *m_st);
void		mut_dest(t_main *m_st);
void 		sleep_func(t_philo *philo);
void	    sleep_func2(t_philo *philo);
void		think_sleep(t_philo *philo);
void		philo_gen(t_main *m_st);
void		check_death(t_philo *philo);
void		num_eat(t_philo *philo);
void		philo_eat(t_philo *philo);
void		sleep_round(t_philo *philo);
void	    change_val(t_philo *philo);
int			check_all_eat(t_philo *philo);
void        free_philo(t_main *m_st);
int         check_flag(t_philo *philo);
long int	tm_tasks(t_philo *philo);
void        print_tasks(t_philo *philo);
void	    ft_sleep(t_philo *philo, int task_tm);
void        ft_sleep2(t_philo *philo);
void        print_t(t_philo *philo, char *s1, char *s2);

#endif