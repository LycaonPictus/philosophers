/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 02:58:57 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	start_eating(t_philo *ph, struct timeval *now)
{
	set_time(&ph->last_thinking);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, *now), ph->id);
	pthread_mutex_unlock(&ph->rules->mutex);
	ph_eat(ph);
}

static void	ph_take_fork(t_philo *ph, int *fork_ptr)
{
	struct timeval	now;

	now = current_time(ph->rules);
	if (fork_ptr != ph->left_fork && fork_ptr != ph->right_fork)
		return ;
	if (fork_ptr == ph->left_fork && *fork_ptr == 0)
		*(ph->left_fork) = 2;
	else if (fork_ptr == ph->right_fork && *fork_ptr == 0)
		*(ph->right_fork) = 1;
	else
		return ;
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, now), ph->id);
}

static void	take_available_forks(t_philo *ph)
{
	struct timeval	now;

	now = current_time(ph->rules);
	if (*(ph->left_fork) == 0 && *(ph->right_fork) == 0)
	{
		ph_take_fork(ph, ph->left_fork);
		ph_take_fork(ph, ph->right_fork);
	}
	else if (*(ph->left_fork) == 0)
		ph_take_fork(ph, ph->left_fork);
	else if (*(ph->right_fork) == 0)
		ph_take_fork(ph, ph->right_fork);
	if (*(ph->left_fork) == 2 && *(ph->right_fork) == 1)
		start_eating(ph, &now);
	else
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		usleep(10);
		ph_think(ph);
	}
}

static void	wait_even(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		ph->try_again = !ph->try_again;
		if (ph->try_again)
		{
			pthread_mutex_unlock(&ph->rules->mutex);
			usleep(100);
			pthread_mutex_lock(&ph->rules->mutex);
		}
	}
}

void	ph_think(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->mutex);
	if (check_ending(ph))
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		return ;
	}
	wait_even(ph);
	take_available_forks(ph);
}
