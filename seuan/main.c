/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:28 by seuan             #+#    #+#             */
/*   Updated: 2021/08/06 02:01:13 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_info(t_info *info, char **argv)
{
    init_info(&info, argv);
    init_fork(&info);
    init_philo(&info);
}

int main(int argc, char **argv)
{
    int i;
    t_info info;

    if (!(argc == 5 || argc == 6))
        return (0);
    info.init_time = current_time();
    i = -1;
    while (++i < info.num_philo)
    {
        info.philo[i].th_time = current_time();
        if (pthread_create(&(info.philo[i].thread), NULL, &philosopher, &info.philo[i]))
            return (printf("Failed create thread\n"));
        if (pthread_create(&(info.philo[i].monitor), NULL, &monitor, &info.philo[i]))
            return (printf("Failed create thread\n"));
        usleep(100);
    }
    i = -1;
    while (++i < info.num_philo)
    {
        if (pthread_join(info.philo[i].thread, NULL))
            return (printf("Failed to join thread.\n"));
        if (pthread_join(info.philo[i].monitor, NULL))
            return (printf("Failed to join thread.\n"));
    }
    return 0;
}