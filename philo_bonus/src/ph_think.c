/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 04:28:27 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo_bonus/inc/philo_bonus.h"

static void	start_eating(t_philo_b *ph, struct timeval *now)
{
	set_time(&ph->last_thinking);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, *now), ph->id);
	sem_post(ph->rules->semaphore);
	ph_eat(ph);
}

static void	ph_take_fork(t_philo_b *ph)
{
	struct timeval	now;

	now = current_time(ph->rules);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, now), ph->id);
}

static void	take_available_forks(t_philo_b *ph)
{
	struct timeval	now;

	now = current_time(ph->rules);
	sem_wait(ph->rules->fork_sem);
	ph_take_fork(ph);
	ph_take_fork(ph);
	start_eating(ph, &now);
}

void	ph_think(t_philo_b *ph)
{
	sem_wait(ph->rules->semaphore);
	if (check_ending(ph))
	{
		sem_post(ph->rules->semaphore);
		return ;
	}
	take_available_forks(ph);
}
