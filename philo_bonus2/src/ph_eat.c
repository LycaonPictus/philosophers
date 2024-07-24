/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:05:07 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 20:02:17 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	end_and_sleep(t_philo *ph)
{
	ph->meals++;
	pthread_mutex_lock(&ph->rules->mutex);
	if (ph->rules->num_meals && ph->meals == ph->rules->num_meals)
		ph->rules->completed_goals++;
	pthread_mutex_unlock(&ph->rules->mutex);
	pthread_mutex_lock(ph->left_fork_mutex);
	*(ph->left_fork) = 0;
	pthread_mutex_unlock(ph->left_fork_mutex);
	pthread_mutex_lock(ph->right_fork_mutex);
	*(ph->right_fork) = 0;
	pthread_mutex_unlock(ph->right_fork_mutex);
	pthread_mutex_lock(&ph->rules->print_mutex);
	printf("%i %i is sleeping\n",
		delta_time(ph->rules->start_time, current_time(ph->rules)), ph->id);
	pthread_mutex_unlock(&ph->rules->print_mutex);
	ph_sleep(ph);
}

void	ph_eat(t_philo *ph)
{
	unsigned int	time_eating;

	pthread_mutex_lock(&ph->rules->mutex);
	if (check_ending(ph, ph->rules))
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		return ;
	}
	pthread_mutex_unlock(&ph->rules->mutex);
	set_time(&ph->last_food);
	time_eating = delta_time(ph->last_thinking, ph->last_food);
	if (time_eating < ph->rules->time_to_eat)
	{
		usleep(10);
		ph_eat(ph);
	}
	else
		end_and_sleep(ph);
}
