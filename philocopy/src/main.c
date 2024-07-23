/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/19 16:58:26 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo2.h>

void	free4(void *p1, void *p2, void *p3, void *p4)
{
	free(p1);
	free(p2);
	free(p3);
	free(p4);
}

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
		ph[i].id = i + 1;
		ph[i].meals = 0;
		ph[i].right_fork = &rules->forks[i];
		ph[i].right_fork_mutex = &rules->fork_mutex[i];
		ph[i].try_again = 0;
		if (i == 0)
		{
			ph[i].left_fork = &rules->forks[rules->num_phil - 1];
			ph[i].left_fork_mutex = &rules->fork_mutex[rules->num_phil - 1];
		}
		else
		{
			ph[i].left_fork = &rules->forks[i - 1];
			ph[i].left_fork_mutex = &rules->fork_mutex[i - 1];
		}
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

int	init_forks(t_rules	*rules)
{
	unsigned int 	i;

	i = 0;
	rules->forks = malloc(sizeof(int) * rules->num_phil);
	rules->fork_mutex = malloc(sizeof(pthread_mutex_t) * rules->num_phil);
	if (!rules->forks || !rules->forks)
	{
		write(2, "Allocation error.\n", 18);
		free4(rules->forks, rules->fork_mutex, NULL, NULL);
		return (1);
	}
	while (i < rules->num_phil)
	{
		rules->forks[i] = 0;
		if (pthread_mutex_init(&rules->fork_mutex[i], NULL))
		{
			while (i-- > 0)
				pthread_mutex_destroy(&rules->fork_mutex[i]);
			free4(rules->forks, rules->fork_mutex, NULL, NULL);
			write(2, "Mutex init error.\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_mutex(t_rules *rules)
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
	rules->ready = 0;
	rules->forks = NULL;
	rules->fork_mutex = NULL;
	return (init_forks(rules));
}


int	main(int argc, char **argv)
{
	unsigned int	i;
	t_rules			rules;
	t_philo			*ph;

	ph = NULL;
	init_mutex(&rules);
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	ph = create_philos(&rules);
	if (!ph)
	{
		free4(rules.forks, rules.fork_mutex, NULL, NULL);
		return (1);
	}
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	i = 0;
	while (i < rules.num_phil)
		pthread_mutex_destroy(&rules.fork_mutex[i++]);
	pthread_mutex_destroy(&rules.mutex);
	pthread_mutex_destroy(&rules.print_mutex);
	free4(rules.forks, rules.fork_mutex, ph, NULL);
	return (0);
}
