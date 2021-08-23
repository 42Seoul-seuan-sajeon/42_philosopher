/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:44:40 by seuan             #+#    #+#             */
/*   Updated: 2021/08/24 02:08:23 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_eat(t_philo *philo)
{
    if (philo->info->num_philo == 1)
    {
        pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
        print_th_status(philo, FORK);
        while(!philo->info->th_is_dead)
            usleep(1000);
        pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
    }
    else
    {
        pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
        print_th_status(philo, FORK);
        pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
        print_th_status(philo, FORK);
        pthread_mutex_lock(&philo->philo_lock);
        print_th_status(philo, EAT);
        philo->th_time = current_time();
        pthread_mutex_unlock(&philo->philo_lock);
        while (current_time() - philo->th_time <= philo->info->time_eat && !philo->info->th_is_dead)
            usleep(1000);
        pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
        pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);
        philo->cnt_eat++;
    }
}

void philo_sleep(t_philo *philo)
{
    int sleep_time;
    
    sleep_time = current_time();
    print_th_status(philo, SLEEP);
    while(current_time() - sleep_time <= philo->info->time_sleep && !philo->info->th_is_dead)
        usleep(1000);
}

void philo_think(t_philo *philo)
{
    print_th_status(philo, THINK);
}

void *philosopher(void *arg)
{
    t_philo *philo;

    philo = arg;
    if (philo->id % 2 != 0)
        usleep(1000 * philo->info->time_eat);
    while (!philo->info->th_is_dead)
    {
        if (philo->cnt_eat == philo->info->must_eating)
            break;
        philo_eat(philo);
        philo_sleep(philo);        
        philo_think(philo);        
    }
    return NULL;
}