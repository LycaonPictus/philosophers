/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timereg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:01:28 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 15:05:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	set_time(struct timeval *time)
{
	int	error;

	error = gettimeofday(time, NULL);
	if (error)
		write(2, "Error getting the time\n", 23);
	return (error);
}

int	delta_time(struct timeval time1, struct timeval time2)
{
	int	delta_s;
	int	delta_us;

	delta_s = time2.tv_sec - time1.tv_sec;
	delta_us = time2.tv_usec - time1.tv_usec;
	if (delta_us > 500000)
		delta_us += 1000;
	return (delta_s * 1000 + delta_us / 1000);
}

struct timeval	current_time(t_rules_b *rules)
{
	struct timeval	current_time;

	if (set_time(&current_time))
		rules->exit_all = 1;
	return (current_time);
}
