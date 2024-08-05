/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timereg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:01:28 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 18:37:54 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

int	set_time(struct timeval *time)
{
	int	error;

	error = gettimeofday(time, NULL);
	if (error)
		write(2, "Error getting the time\n", 23);
	else
		time->tv_usec -= time->tv_usec % 1000;
	return (error);
}

int	delta_time(struct timeval time1, struct timeval time2)
{
	int	delta_s;
	int	delta_us;

	delta_s = time2.tv_sec - time1.tv_sec;
	delta_us = time2.tv_usec - time1.tv_usec;
	return (delta_s * 1000 + delta_us / 1000);
}

struct timeval	current_time(void)
{
	struct timeval	current_time;

	set_time(&current_time);
	return (current_time);
}
