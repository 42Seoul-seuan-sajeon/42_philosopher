/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seuan <seuan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 02:01:57 by seuan             #+#    #+#             */
/*   Updated: 2021/08/26 16:34:01 by seuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(t_info *info, char *msg, int type)
{
	printf("[%s ", msg);
	if (type == MALLOC_FAIL)
		printf("%s\n", "MALLOC_FAIL]");
	else if (type == MUTEX_FAIL)
		printf("%s\n", "MUTEX_FAIL]");
	else if (type == THREAD_CREATE_FAIL)
		printf("%s\n", "THREAD_CREATE_FAIL]");
	else if (type == THREAD_JOIN_FAIL)
		printf("%s\n", "THREAD_JOIN_FAIL]");
	free_all(info);
	return (1);
}
