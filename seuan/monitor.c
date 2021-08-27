/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:44:49 by seuan             #+#    #+#             */
/*   Updated: 2021/08/27 16:20:26 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_cnt_eat_full(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (info->philo[i].cnt_eat < info->must_eating)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_info	*info;

	philo = arg;
	info = philo->info;
	while (!philo->info->th_is_dead)
	{
		pthread_mutex_lock(&philo->th_lock);
		if (current_time() - philo->th_wait_time >= philo->info->time_die)
		{
			print_th_status(philo, DIE);
			philo->info->th_is_dead = 1;
			pthread_mutex_unlock(&philo->th_lock);
			break ;
		}
		else if (philo->info->must_eating != -1 && philo_cnt_eat_full(info))
		{
			pthread_mutex_unlock(&philo->th_lock);
			philo->info->th_is_dead = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->th_lock);
		usleep(100);
	}
	return (NULL);
}
