/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:28 by seuan             #+#    #+#             */
/*   Updated: 2021/08/24 04:15:52 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_error(int argc, char **argv)
{	
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (1);
		i++;
	}
	if (!(argc == 5 || argc == 6))
		return (1);
	return (0);
}

void	set_info(t_info *info, char **argv)
{
	init_info(info, argv);
	init_fork(info);
	init_philo(info);
}

int	create_join_thread(t_info info)
{
	int	i;

	i = -1;
	while (++i < info.num_philo)
	{
		info.philo[i].th_time = current_time();
		if (pthread_create(&(info.philo[i].thread), NULL, &philosopher, \
							&info.philo[i]))
			return (printf("Failed create thread\n"));
		if (pthread_create(&(info.philo[i].monitor), NULL, &monitor, \
							&info.philo[i]))
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (is_error(argc, argv))
		return (0);
	set_info(&info, argv);
	info.init_time = current_time();
	create_join_thread(info);
	return (0);
}
