/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:05:07 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 15:50:32 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	end_and_sleep(t_philo_b *ph, struct timeval *now)
{
	ph->meals++;
	if (ph->rules->num_meals && ph->meals == ph->rules->num_meals)
		ph->rules->completed_goals++;
	sem_post(ph->fork_sem);
	printf("%i %i is sleeping\n",
		delta_time(ph->rules->start_time, *now), ph->id);
	if (check_ending(ph, rules))
	{
		sem_post(ph->rules->semaphore);
		return ;
	}
	sem_post(ph->rules->semaphore);
	ph_sleep(ph);
}

void	ph_eat(t_philo_b *ph)
{
	unsigned int	time_eating;
	struct timeval	now;

	sem_wait(ph->rules->semaphore);
	if (check_ending(ph, rules))
	{
		sem_post(ph->rules->semaphore);
		return ;
	}
	now = current_time(ph->rules);
	time_eating = delta_time(ph->last_thinking, now);
	if (time_eating < ph->rules->time_to_eat)
	{
		set_time(&ph->last_food);
		sem_post(ph->rules->semaphore);
		usleep(10);
		ph_eat(ph);
	}
	else
		end_and_sleep(ph, &now);
}
