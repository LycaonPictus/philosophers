/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 15:50:32 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	start_eating(t_philo_b *ph, struct timeval *now)
{
	set_time(&ph->last_thinking);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, *now), ph->id);
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

	sem_wait(ph->fork_sem);
	now = current_time(ph->rules);
	ph_take_fork(ph);
	ph_take_fork(ph);
	start_eating(ph, &now);
}

void	ph_think(t_philo_b *ph)
{
	sem_wait(ph->rules->semaphore);
	if (check_ending(ph, rules))
	{
		sem_post(ph->rules->semaphore);
		return ;
	}
	sem_post(ph->rules->semaphore);
	take_available_forks(ph);
}
