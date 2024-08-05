/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:04:28 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 16:42:37 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_action(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->mutex);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		usleep(500);
		pthread_mutex_lock(&ph->rules->mutex);
	}
	while (!ph->rules->exit_all)
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		ph_think(ph);
		pthread_mutex_lock(&ph->rules->mutex);
	}
	pthread_mutex_unlock(&ph->rules->mutex);
}

void	*init_philo(void *ptr)
{
	t_philo	*ph;

	ph = ptr;
	pthread_mutex_lock(&ph->rules->mutex);
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	pthread_mutex_unlock(&ph->rules->mutex);
	start_action(ph);
	return (ptr);
}

void	set_attributes(t_philo *ph, unsigned int index)
{
	t_rules	*rules;

	rules = ph->rules;
	ph->id = index + 1;
	ph->meals = 0;
	ph->right_fork = &rules->forks[index];
	ph->right_fork_mutex = &rules->fork_mutex[index];
	if (index == 0)
	{
		ph->left_fork = &rules->forks[rules->num_phil - 1];
		ph->left_fork_mutex = &rules->fork_mutex[rules->num_phil - 1];
	}
	else
	{
		ph->left_fork = &rules->forks[index - 1];
		ph->left_fork_mutex = &rules->fork_mutex[index - 1];
	}
}

t_philo	*create_philos(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;

	i = 0;
	ph = malloc(sizeof(t_philo) * rules->num_phil);
	if (!ph)
		return (NULL);
	while (i < rules->num_phil)
	{
		ph[i].rules = rules;
		set_attributes(&ph[i], i);
		if (i == 0)
			pthread_mutex_lock(&rules->mutex);
		if (pthread_create(&ph[i].thread, NULL, init_philo, &ph[i]))
			return (NULL);
		i++;
	}
	set_time(&rules->start_time);
	pthread_mutex_unlock(&rules->mutex);
	return (ph);
}
