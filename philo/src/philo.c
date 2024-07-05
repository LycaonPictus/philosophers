/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/05 14:01:54 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_ready(t_philo *ph, t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex);
	if (ph->id == rules->num_phil)
	{
		set_time(&rules->start_time);
		rules->ready = 1;
	}
	pthread_mutex_unlock(&rules->mutex);
}

void	wait_ready(t_rules *rules)
{
	pthread_mutex_lock(&rules->mutex);
	while (!rules->ready)
	{
		pthread_mutex_unlock(&rules->mutex);
		pthread_mutex_lock(&rules->mutex);
	}
	pthread_mutex_unlock(&rules->mutex);
}

void	start_action(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->mutex);
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
	set_ready(ph, ph->rules);
	wait_ready(ph->rules);
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	start_action(ph);
	return (ptr);
}

t_philo	*create_phils(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;

	i = 0;
	ph = malloc(sizeof(t_philo) * rules->num_phil);
	while (i < rules->num_phil)
	{
		ph[i].rules = rules;
		ph[i].id = i + 1;
		ph[i].meals = 0;
		ph[i].right_fork = &rules->forks[i];
		ph[i].try_again = 0;
		if (i == 0)
			ph[i].left_fork = &rules->forks[rules->num_phil - 1];
		else
			ph[i].left_fork = &rules->forks[i - 1];
		if (pthread_create(&ph[i].thread, NULL, init_philo, &ph[i]))
		{
			write(2, "Error: pthread failure.\n", 24);
			return (NULL);
		}
		i++;
	}
	return (ph);
}

void	init_table(t_rules	*rules)
{
	unsigned int	i;

	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->forks = malloc(sizeof(int) * rules->num_phil);
	rules->ready = 0;
	if (!rules->forks)
		exit_fn(1, "Error allocating the forks.\n");
	i = 0;
	while (i < rules->num_phil)
		rules->forks[i++] = 0;
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_rules			rules;
	t_philo			*ph;

	parse_args(argc, argv, &rules);
	init_table(&rules);
	if (pthread_mutex_init(&rules.mutex, NULL))
		write(2, "Init mutex failed.\n", 19);
	ph = create_phils(&rules);
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	pthread_mutex_destroy(&rules.mutex);
	free(ph);
	free(rules.forks);
	return (0);
}
