/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 00:11:28 by seuan             #+#    #+#             */
/*   Updated: 2021/08/26 16:33:08 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argc_argv(int argc, char **argv)
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

int	create_asset(t_info *info, char **argv)
{
	if (create_info(info, argv))
		return (1);
	if (create_fork(info))
		return (1);
	if (create_philo(info))
		return (1);
	return (0);
}

int	th_create_and_join(t_info info)
{
	int	i;

	i = -1;
	while (++i < info.num_philo)
	{
		info.philo[i].th_wait_time = current_time();
		if (pthread_create(&(info.philo[i].thread), NULL, &philosopher, \
							&info.philo[i]))
			return (print_error(&info, "Failed create\n", THREAD_CREATE_FAIL));
		if (pthread_create(&(info.philo[i].monitor), NULL, &monitor, \
							&info.philo[i]))
			return (print_error(&info, "Failed create\n", THREAD_CREATE_FAIL));
		usleep(100);
	}
	i = -1;
	while (++i < info.num_philo)
	{
		if (pthread_join(info.philo[i].thread, NULL))
			return (print_error(&info, "Failed join\n", THREAD_JOIN_FAIL));
		if (pthread_join(info.philo[i].monitor, NULL))
			return (print_error(&info, "Failed join\n", THREAD_JOIN_FAIL));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_argc_argv(argc, argv))
		return (1);
	if (create_asset(&info, argv))
		return (1);
	info.init_time = current_time();
	if (th_create_and_join(info))
		return (1);
	free_all(&info);
	return (0);
}
