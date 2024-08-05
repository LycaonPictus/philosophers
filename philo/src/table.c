/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:06:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 15:26:46 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_mutexes(t_rules *rules, unsigned int n_forks)
{
	unsigned int	i;

	pthread_mutex_destroy(&rules->mutex);
	pthread_mutex_destroy(&rules->print_mutex);
	i = 0;
	while (i < n_forks)
		pthread_mutex_destroy(&rules->fork_mutex[i++]);
}

static int	init_forks(t_rules	*rules)
{
	unsigned int	i;

	i = 0;
	rules->forks = malloc(sizeof(int) * rules->num_phil);
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t) * rules->num_phil);
	if (!rules->forks || !rules->forks)
	{
		write(2, "Allocation error.\n", 18);
		free(rules->forks);
		free(rules->fork_mutex);
		return (1);
	}
	while (i < rules->num_phil)
	{
		rules->forks[i] = 0;
		if (pthread_mutex_init(&rules->fork_mutex[i], NULL))
		{
			destroy_mutexes(rules, i);
			free(rules->forks);
			free(rules->fork_mutex);
			write(2, "Mutex init error.\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutex(t_rules *rules)
{
	if (pthread_mutex_init(&rules->mutex, NULL))
	{
		write(2, "Init mutex failed.\n", 19);
		return (1);
	}
	if (pthread_mutex_init(&rules->print_mutex, NULL))
	{
		pthread_mutex_destroy(&rules->mutex);
		write(2, "Init mutex failed.\n", 19);
		return (1);
	}
	return (0);
}

int	init_table(t_rules *rules)
{
	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->forks = NULL;
	rules->fork_mutex = NULL;
	if (init_mutex(rules))
		return (1);
	return (init_forks(rules));
}
