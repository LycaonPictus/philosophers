/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timereg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:01:28 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 23:25:01 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	set_time(struct timeval *time)
{
	int						time_error;

	time_error = gettimeofday(time, NULL);
	if (time_error)
		exit_fn(1, "Failure setting the time\n");
}
