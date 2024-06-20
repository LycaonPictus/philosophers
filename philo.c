/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 23:34:32 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	debugfd;

void	*do_something(void *ptr)
{
	t_philo	*ph;

	ph = ptr;
	ph_think(ph);
	return (ptr);
}

void	create_phils(t_rules *rules, pthread_t *tid)
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
		ph[i].last_food = rules->current_time;
		ph[i].right_fork = &rules->forks[i];
		if (i == 0)
			ph[i].left_fork = &rules->forks[rules->num_phil - 1];
		else
			ph[i].left_fork = &rules->forks[i - 1];
		if (pthread_create(&tid[i], NULL, do_something, &ph[i]))
		{
			free(tid);
			write(2, "Error: pthread failure.\n", 24);
		}
		i++;
	}
	free(ph);
}

void	init_table(t_rules	*rules)
{
	int	i;

	rules->phil_ok = 1;
	rules->forks = malloc(sizeof(int) * rules->num_phil);
	if (!rules->forks)
		exit_fn(1, "Error allocating the forks.\n");
	i = 0;
	while (i < rules->num_phil)
		rules->forks[i++] = 1;
	set_time(&rules->current_time);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	*tid;

	debugfd = open("_debug", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	parse_args(argc, argv, &rules);
	tid = malloc(sizeof(pthread_t) * rules.num_phil);
	init_table(&rules);
	create_phils(&rules, tid);
	int i = 0;
	while (i < rules.num_phil)
		pthread_join(tid[i++], NULL);
	free(tid);
	free(rules.forks);
	dprintf(debugfd, "End of program.\n");
	return (0);
}
