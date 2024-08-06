/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ending.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/08/06 20:52:25 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_bad_ending(t_philo *ph, t_rules *rules)
{
	rules->exit_all = 1;
	pthread_mutex_lock(&rules->print_mutex);
	printf("%i %i died\n", delta_time(rules->start_time, current_time(rules)),
		ph->id);
	pthread_mutex_unlock(&rules->print_mutex);
}

void	print_good_ending(t_rules *rules)
{
	rules->exit_all = 1;
	pthread_mutex_lock(&rules->print_mutex);
	printf("- All philosophers have eaten %i times -\n", rules->num_meals);
	pthread_mutex_unlock(&rules->print_mutex);
}

int	check_ending(t_philo *ph, t_rules *rules)
{
	unsigned int	time_hungry;

	pthread_mutex_lock(&ph->rules->mutex);
	if (rules->exit_all)
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		return (1);
	}
	time_hungry = delta_time(ph->last_food, current_time(rules));
	if (time_hungry >= rules->time_to_die)
	{
		print_bad_ending(ph, rules);
		pthread_mutex_unlock(&ph->rules->mutex);
		return (1);
	}
	if (rules->num_meals && rules->completed_goals == rules->num_phil)
	{
		print_good_ending(rules);
		pthread_mutex_unlock(&ph->rules->mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph->rules->mutex);
	return (0);
}
