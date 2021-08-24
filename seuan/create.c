/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:32:01 by seuan             #+#    #+#             */
/*   Updated: 2021/08/25 01:59:02 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_fork(t_info *info)
{
	int	i;

	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
					info->num_philo);
	if (!info->fork)
		return (printf("Failed to allocate memory.\n"));
	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
			return (printf("Failed to create mutex.\n"));
		i++;
	}
	return (0);
}

int	create_philo(t_info *info)
{
	int	i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
		return (printf("Failed to allocate memory.\n"));
	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i].id = i;
		info->philo[i].info = info;
		info->philo[i].th_wait_time = 0;
		info->philo[i].left_fork_idx = i;
		info->philo[i].right_fork_idx = (i + 1) % info->num_philo;
		info->philo[i].cnt_eat = 0;
		if (pthread_mutex_init(&info->philo[i].th_lock, NULL))
			return (printf("Failed to create mutex.\n"));
		i++;
	}
	return (0);
}

int	create_info(t_info *info, char **argv)
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
	if (pthread_mutex_init(&info->th_status, NULL))
		return (printf("Failed to create mutex.\n"));
	return (0);
}
