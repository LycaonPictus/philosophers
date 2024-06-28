/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:07:46 by jholland          #+#    #+#             */
/*   Updated: 2024/06/25 21:17:53 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_deaths(t_philo *ph)
{
	int				time_hungry;
	struct timeval	now;

	if (ph->rules->exit_all)
		return (1);
	now = current_time(ph->rules);
	time_hungry = delta_time(ph->last_food, now);
	if (time_hungry >= ph->rules->time_to_die)
	{
		ph->rules->exit_all = 1;
		printf("%i %i died\n", delta_time(ph->rules->start_time, now), ph->id);
		return (1);
	}
	return (0);
}
