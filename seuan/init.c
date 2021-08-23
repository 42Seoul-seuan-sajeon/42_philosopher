/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:32:01 by seuan             #+#    #+#             */
/*   Updated: 2021/08/24 02:21:08 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_fork(t_info *info)
{
    int i;

    info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_philo);
    i = 0;
    while (i < info->num_philo)
    {
        pthread_mutex_init(&info->fork[i], NULL);
        i++;
    }
}

void    init_philo(t_info *info)
{
    int i;

    info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
    i = 0;
    while (i < info->num_philo)
    {
        info->philo[i].id = i;
        info->philo[i].info = info;
        info->philo[i].th_time = 0;
        info->philo[i].left_fork = i;
        info->philo[i].right_fork = (i + 1) % info->num_philo;
        info->philo[i].cnt_eat = 0;
        pthread_mutex_init(&info->philo[i].philo_lock, NULL);
        i++;
    }
}

void    init_info(t_info *info, char **argv)
{
    info->num_philo = ft_atoi(argv[1]);
    info->time_die = ft_atoi(argv[2]);
    info->time_eat = ft_atoi(argv[3]);
    info->time_sleep = ft_atoi(argv[4]);
    info->th_is_dead = 0;
    info->init_time = 0;
    info->must_eating = -1;
    if (argv[5])
        info->must_eating = ft_atoi(argv[5]);
    pthread_mutex_init(&info->th_status, NULL);
}