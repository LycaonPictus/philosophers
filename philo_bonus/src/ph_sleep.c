/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:06:41 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 23:21:02 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_bonus/inc/philo_bonus.h"

void	ph_sleep(t_philo_b *ph)
{
	unsigned int	time_sleeping;

	sem_wait(ph->fork_sem);
	if (check_ending(ph))
	{
		sem_post(ph->fork_sem);
		return ;
	}
	sem_post(ph->fork_sem);
	time_sleeping = delta_time(ph->last_food, current_time(ph->rules));
	if (time_sleeping < ph->rules->time_to_sleep)
	{
		usleep(10);
		ph_sleep(ph);
	}
}
