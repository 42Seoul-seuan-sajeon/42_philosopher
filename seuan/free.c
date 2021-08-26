/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 00:58:04 by seuan             #+#    #+#             */
/*   Updated: 2021/08/26 16:34:04 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->philo[i].th_lock);
		i++;
	}
	pthread_mutex_destroy(&info->th_status);
	free(info->fork);
	free(info->philo);
}
