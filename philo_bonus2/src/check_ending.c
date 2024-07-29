/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/07/29 19:25:29 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

int	check_ending(t_philo *ph, t_rules *rules)
{
	unsigned int	time_hungry;
	struct timeval	now;

	if (rules->exit_all)
		return (1);
	now = current_time(rules);
	time_hungry = delta_time(ph->last_food, now);
	if (time_hungry >= rules->time_to_die)
	{
		rules->exit_all = 1;
		pthread_mutex_lock(&rules->print_mutex);
		printf("%i %i died\n", delta_time(rules->start_time, now), ph->id);
		pthread_mutex_unlock(&rules->print_mutex);
		return (1);
	}
	if (rules->num_meals && rules->completed_goals == rules->num_phil)
	{
		pthread_mutex_lock(&rules->print_mutex);
		printf("- All philosophers has eaten %i times -\n", rules->num_meals);
		pthread_mutex_unlock(&rules->print_mutex);
		rules->exit_all = 1;
		return (1);
	}
	return (0);
}
