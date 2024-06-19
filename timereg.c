/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timereg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:01:28 by jholland          #+#    #+#             */
/*   Updated: 2024/06/19 19:06:07 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	set_time(struct timeval *time)
{
	int	time_error;

	time_error = gettimeofday(time, NULL);
	if (time_error)
	{
		dprintf(debugfd, "Failure setting the time\n");
		return (0);
	}
	else
	{
		dprintf(debugfd, "Success setting the time\n");
		return (1);
	}
}
