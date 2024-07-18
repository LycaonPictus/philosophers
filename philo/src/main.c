/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 16:57:17 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_action(t_philo *ph)
{
	pthread_mutex_lock(&ph->rules->mutex);
	if (ph->id % 2 == 0)
	{
		ph->try_again = !ph->try_again;
		if (ph->try_again)
		{
			pthread_mutex_unlock(&ph->rules->mutex);
			usleep(500);
			pthread_mutex_lock(&ph->rules->mutex);
		}
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
		if (i == 0)
			pthread_mutex_lock(&rules->mutex);
		if (pthread_create(&ph[i].thread, NULL, init_philo, &ph[i]))
		{
			write(2, "Error: pthread failure.\n", 24);
			return (NULL);
		}
		i++;
	}
	set_time(&rules->start_time);
	pthread_mutex_unlock(&rules->mutex);
	return (ph);
}

int	init_table(t_rules	*rules)
{
	unsigned int	i;

	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->ready = 0;
	rules->forks = malloc(sizeof(int) * rules->num_phil);
	if (!rules->forks)
	{
		write(2, "Error allocating the forks.\n", 28);
		return (1);
	}
	i = 0;
	while (i < rules->num_phil)
		rules->forks[i++] = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_rules			rules;
	t_philo			*ph;

	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	if (pthread_mutex_init(&rules.mutex, NULL))
		write(2, "Init mutex failed.\n", 19);
	ph = create_phils(&rules);
	if (!ph)
	{
		free(rules.forks);
		
	}
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	pthread_mutex_destroy(&rules.mutex);
	free(ph);
	free(rules.forks);
	return (0);
}
