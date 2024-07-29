/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:06:41 by jholland          #+#    #+#             */
/*   Updated: 2024/07/29 19:25:40 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

void	ph_sleep(t_philo *ph)
{
	unsigned int	time_sleeping;

	pthread_mutex_lock(&ph->rules->mutex);
	if (check_ending(ph, ph->rules))
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		return ;
	}
	pthread_mutex_unlock(&ph->rules->mutex);
	time_sleeping = delta_time(ph->last_food, current_time(ph->rules));
	if (time_sleeping < ph->rules->time_to_sleep)
	{
		usleep(10);
		ph_sleep(ph);
		return ;
	}
}
