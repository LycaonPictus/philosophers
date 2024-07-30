/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:06:41 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 18:50:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

int	ph_sleep(t_philo *ph)
{
	unsigned int	time_sleeping;
	int				check_result;
	int				sleep_result;

	check_result = check_ending(ph, ph->rules);
	if (check_result)
		return (check_result);
	time_sleeping = delta_time(ph->last_food, current_time());
	if (time_sleeping < ph->rules->time_to_sleep)
	{
		usleep(10);
		sleep_result = ph_sleep(ph);
		if (sleep_result)
			return (sleep_result);
	}
	return (0);
}
