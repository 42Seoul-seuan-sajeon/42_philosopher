/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:44:40 by seuan             #+#    #+#             */
/*   Updated: 2021/08/06 00:45:28 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher(void *arg)
{
    int sleep_time;
    t_philo *philo;

    // thread 생성 시 넘어오는 매개변수 받기
    philo = arg;

    // 짝수 thread에 대해 usleep을 지정함으로써 홀수 thread가 우선적으로 실행되게 함.
    if (philo->id % 2 == 0)
        usleep(1000 * philo->info->time_eat);

    // thread가 실행되는 가상의 시간 설정
    while (!philo->info->th_is_dead)
    {
        // eating
        pthread_mutex_lock(&philo->info->fork[philo->right_fork]);
        print_th_status(philo, FORK);
        pthread_mutex_lock(&philo->info->fork[philo->left_fork]);
        print_th_status(philo, FORK);
        pthread_mutex_lock(&philo->philo_lock);
        print_th_status(philo, EAT);
        philo->th_time = current_time();
        while (current_time() - philo->th_time <= philo->info->time_eat && !philo->info->th_is_dead)
            usleep(1000);
        pthread_mutex_unlock(&philo->philo_lock);
        pthread_mutex_unlock(&philo->info->fork[philo->right_fork]);
        pthread_mutex_unlock(&philo->info->fork[philo->left_fork]);

        // sleeping
        sleep_time = current_time();
        print_th_status(philo, SLEEP);
        while(current_time() - sleep_time <= philo->info->time_sleep && !philo->info->th_is_dead)
            usleep(1000);

        // thinking
        print_th_status(philo, THINK);
    }
    return NULL;
}