/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:05:07 by jholland          #+#    #+#             */
/*   Updated: 2024/06/25 23:53:35 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	end_and_sleep(t_philo *ph, struct timeval *now)
{
	ph->meals++;
	*(ph->left_fork) = 0;
	*(ph->right_fork) = 0;
	printf("%i %i is sleeping\n",
		delta_time(ph->rules->start_time, *now), ph->id);
	pthread_mutex_unlock(&ph->rules->mutex);
	ph_sleep(ph);
}

void	ph_eat(t_philo *ph)
{
	unsigned int	time_eating;
	struct timeval	now;
	pthread_mutex_lock(&ph->rules->mutex);
	if (check_deaths(ph))
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		return ;
	}
	now = current_time(ph->rules);
	time_eating = delta_time(ph->last_thinking, now);
	if (time_eating < ph->rules->time_to_eat)
	{
		set_time(&ph->last_food);
		pthread_mutex_unlock(&ph->rules->mutex);
		usleep(10);
		ph_eat(ph);
	}
	else
		end_and_sleep(ph, &now);
}
