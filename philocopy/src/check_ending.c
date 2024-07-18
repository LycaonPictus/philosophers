/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 20:42:31 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	check_ending(t_philo *ph)
{
	unsigned int	time_hungry;
	struct timeval	now;

	if (ph->rules->exit_all)
		return (1);
	now = current_time(ph->rules);
	time_hungry = delta_time(ph->last_food, now);
	if (time_hungry >= ph->rules->time_to_die)
	{
		ph->rules->exit_all = 1;
		pthread_mutex_lock(&ph->rules->print_mutex);
		printf("%i %i died\n", delta_time(ph->rules->start_time, now), ph->id);
		pthread_mutex_unlock(&ph->rules->print_mutex);
		return (1);
	}
	if (ph->rules->num_meals && ph->rules->completed_goals == ph->rules->num_phil)
	{
		pthread_mutex_lock(&ph->rules->print_mutex);
		printf("\n-- Every philosopher has eaten %i times --\n", ph->rules->num_meals);
		pthread_mutex_unlock(&ph->rules->print_mutex);
		ph->rules->exit_all = 1;
		return (1);
	}
	return (0);
}
