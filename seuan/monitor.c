/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:44:49 by seuan             #+#    #+#             */
/*   Updated: 2021/08/24 02:41:48 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->info->th_is_dead)
	{
		pthread_mutex_lock(&philo->philo_lock);
		if (philo->cnt_eat == philo->info->must_eating)
		{
			pthread_mutex_unlock(&philo->philo_lock);
			break ;
		}
		else if (current_time() - philo->th_time >= philo->info->time_die)
		{
			print_th_status(philo, DIE);
			philo->info->th_is_dead = 1;
			pthread_mutex_unlock(&philo->philo_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_lock);
		usleep(100);
	}
	return (NULL);
}
