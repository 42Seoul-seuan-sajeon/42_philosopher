/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:17 by seuan             #+#    #+#             */
/*   Updated: 2021/08/25 01:59:02 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_info
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eating;
	int				init_time;
	int				th_is_dead;
	pthread_mutex_t	th_status;
	pthread_mutex_t	*fork;
	t_philo			*philo;
};

struct s_philo
{
	int				id;
	int				th_wait_time;
	int				left_fork_idx;
	int				right_fork_idx;
	int				cnt_eat;
	t_info			*info;
	pthread_t		thread;
	pthread_t		monitor;
	pthread_mutex_t	th_lock;
};

int		create_fork(t_info *info);
int		create_philo(t_info *info);
int		create_info(t_info *info, char **argv);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		current_time(void);
void	print_th_status(t_philo *philo, int th_status);
void	*monitor(void *arg);
void	*philosopher(void *arg);

#endif
