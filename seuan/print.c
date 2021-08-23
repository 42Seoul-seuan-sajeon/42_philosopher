/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:33:38 by seuan             #+#    #+#             */
/*   Updated: 2021/08/24 03:02:42 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_th_status(t_philo *philo, int th_status)
{
	pthread_mutex_lock(&philo->info->th_status);
	if (philo->info->th_is_dead)
	{
		pthread_mutex_unlock(&philo->info->th_status);
		return ;
	}
	printf("[%dms] ", current_time() - philo->info->init_time);
	printf("%d philosopher ", philo->id + 1);
	if (th_status == FORK)
		printf("has taken a fork\n");
	else if (th_status == EAT)
		printf("is eating\n");
	else if (th_status == SLEEP)
		printf("is sleeping\n");
	else if (th_status == THINK)
		printf("is thinking\n");
	else if (th_status == DIE)
		printf("died\n");
	pthread_mutex_unlock(&philo->info->th_status);
}
