/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 11:37:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

int	ph_think(t_philo *ph)
{
	int	check_result;

	sem_wait(ph->fork_sem);
	check_result = check_ending(ph, ph->rules);
	if (check_result)
		return (check_result);
	set_time(&ph->last_thinking);
	sem_wait(ph->print_sem);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	sem_post(ph->print_sem);
	return (ph_eat(ph));
}
