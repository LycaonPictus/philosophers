/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 21:24:34 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

// Last sem_post set in the main function in order to block pending prints
int	check_ending(t_philo *ph, t_rules *rules)
{
	unsigned int	time_hungry;
	struct timeval	now;

	now = current_time();
	time_hungry = delta_time(ph->last_food, now);
	if (time_hungry >= rules->time_to_die)
	{
		sem_wait(ph->print_sem);
		printf("%i %i died\n", delta_time(rules->start_time, now), ph->id);
		return (1);
	}
	if (rules->num_meals && ph->meals == rules->num_meals)
		return (2);
	return (0);
}
