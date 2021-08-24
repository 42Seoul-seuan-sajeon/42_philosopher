/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:44:40 by seuan             #+#    #+#             */
/*   Updated: 2021/08/25 02:04:02 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->info->num_philo == 1)
	{
		pthread_mutex_lock(&philo->info->fork[philo->right_fork_idx]);
		print_th_status(philo, FORK);
		while (!philo->info->th_is_dead)
			usleep(1000);
		pthread_mutex_unlock(&philo->info->fork[philo->right_fork_idx]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->fork[philo->right_fork_idx]);
		print_th_status(philo, FORK);
		pthread_mutex_lock(&philo->info->fork[philo->left_fork_idx]);
		print_th_status(philo, FORK);
		pthread_mutex_lock(&philo->th_lock);
		print_th_status(philo, EAT);
		philo->th_wait_time = current_time();
		pthread_mutex_unlock(&philo->th_lock);
		while (current_time() - philo->th_wait_time <= philo->info->time_eat && \
				!philo->info->th_is_dead)
			usleep(1000);
		pthread_mutex_unlock(&philo->info->fork[philo->right_fork_idx]);
		pthread_mutex_unlock(&philo->info->fork[philo->left_fork_idx]);
		philo->cnt_eat++;
	}
}

void	sleeping(t_philo *philo)
{
	int	sleep_time;

	sleep_time = current_time();
	print_th_status(philo, SLEEP);
	while (current_time() - sleep_time <= philo->info->time_sleep && \
			!philo->info->th_is_dead)
		usleep(1000);
}

void	thinking(t_philo *philo)
{
	print_th_status(philo, THINK);
}

void	*philosopher(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0 && philo->info->num_philo != 1)
		usleep(1000 * philo->info->time_eat);
	while (!philo->info->th_is_dead && \
			philo->cnt_eat != philo->info->must_eating)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
