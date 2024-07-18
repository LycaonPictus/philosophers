/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 20:53:13 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	start_eating(t_philo *ph, struct timeval *now)
{
	set_time(&ph->last_thinking);
	pthread_mutex_lock(&ph->rules->print_mutex);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, *now), ph->id);
	pthread_mutex_unlock(&ph->rules->print_mutex);
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
	pthread_mutex_lock(&ph->rules->print_mutex);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, now), ph->id);
	pthread_mutex_unlock(&ph->rules->print_mutex);
}

static void	take_available_forks(t_philo *ph)
{
	struct timeval	now;

	now = current_time(ph->rules);
	pthread_mutex_lock(ph->left_fork_mutex);
	if (*(ph->left_fork) == 0)
		ph_take_fork(ph, ph->left_fork);
	pthread_mutex_lock(ph->right_fork_mutex);
	if (*(ph->right_fork) == 0)
		ph_take_fork(ph, ph->right_fork);
	if (*(ph->left_fork) == 2 && *(ph->right_fork) == 1)
	{
		pthread_mutex_unlock(ph->left_fork_mutex);
		pthread_mutex_unlock(ph->right_fork_mutex);
		start_eating(ph, &now);
	}
	else
	{
		pthread_mutex_unlock(ph->left_fork_mutex);
		pthread_mutex_unlock(ph->right_fork_mutex);
		usleep(10);
		ph_think(ph);
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
	pthread_mutex_unlock(&ph->rules->mutex);
	take_available_forks(ph);
}
