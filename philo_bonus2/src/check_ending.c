/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 18:42:42 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

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
		sem_post(ph->print_sem);
		return (1);
	}
	if (rules->num_meals && rules->completed_goals == rules->num_phil)
	{
		sem_wait(ph->print_sem);
		printf("- All philosophers has eaten %i times -\n", rules->num_meals);
		sem_post(ph->print_sem);
		return (2);
	}
	return (0);
}
