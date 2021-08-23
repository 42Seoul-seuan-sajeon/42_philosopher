/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:17 by seuan             #+#    #+#             */
/*   Updated: 2021/08/19 22:36:53 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

// philosopher 구조체

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_info
{   
    int num_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eating;
    int init_time;
    int th_is_dead;
    pthread_mutex_t th_status;
    pthread_mutex_t *fork;
    t_philo *philo;
};

struct s_philo
{
    int id;
    int th_time;
    int left_fork;
    int right_fork;
    int cnt_eat;
    t_info *info;
    pthread_t thread;
    pthread_t monitor;
    pthread_mutex_t philo_lock;
};

void	init_fork(t_info *info);
void	init_philo(t_info *info);
void	init_info(t_info *info, char **argv);
void	print_th_status(t_philo *philo, int th_status);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		current_time(void);
void	*monitor(void *arg);
void	*philosopher(void *arg);