/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:05:07 by jholland          #+#    #+#             */
/*   Updated: 2024/07/04 21:48:43 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	end_and_sleep(t_philo *ph, struct timeval *now)
{
	ph->meals++;
	if (ph->rules->num_meals && ph->meals == ph->rules->num_meals)
		ph->rules->completed_goals++;
	*(ph->left_fork) = 0;
	*(ph->right_fork) = 0;
	printf("%i %i is sleeping\n",
		delta_time(ph->rules->start_time, *now) / 1000, ph->id);
}

int	ph_eat(t_philo *ph)
{
	unsigned int	time_eating;
	struct timeval	now;

	if (check_ending(ph))
		return (0);
	now = current_time(ph->rules);
	time_eating = delta_time(ph->last_thinking, now);
	ph->last_food = now;
	if (time_eating < ph->rules->time_to_eat)
		return (1);	
	else
	{
		end_and_sleep(ph, &now);
		return (0);
	}
}
