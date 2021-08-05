/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:28 by seuan             #+#    #+#             */
/*   Updated: 2021/08/06 00:45:26 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    int i = 0;
    t_info info;

    // 올바른 인자 수 여부 체크.
    if (!(argc == 5 || argc == 6))
        return (0);
    init_info(&info, argv);

    // mutex init fork
    init_fork(&info);

    // init philo
    init_philo(&info);

    // pthread_create thread
    info.init_time = current_time();
    i = 0;
    while (i < info.num_philo)
    {
        info.philo[i].th_time = current_time();
        if (pthread_create(&(info.philo[i].thread), NULL, &philosopher, &info.philo[i]))
            return (printf("Failed create thread\n"));
        if (pthread_create(&(info.philo[i].monitor), NULL, &monitor, &info.philo[i]))
            return (printf("Failed create thread\n"));
        usleep(100);
        i++;
    } 
    // pthread_join
    i = 0;
    while (i < info.num_philo)
    {
        if (pthread_join(info.philo[i].thread, NULL))
            return (printf("Failed to join thread.\n"));
        if (pthread_join(info.philo[i].monitor, NULL))
            return (printf("Failed to join thread.\n"));
        i++;
    }
    return 0;
}