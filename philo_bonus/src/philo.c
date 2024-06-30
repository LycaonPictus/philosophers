/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/06/30 21:11:17 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include "../../philo/inc/philo.h"

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

void	wait_ready(t_rules_b *rules)
{
	pthread_mutex_lock(&rules->mutex);
	while (!rules->ready)
	{
		pthread_mutex_unlock(&rules->mutex);
		pthread_mutex_lock(&rules->mutex);
	}
	pthread_mutex_unlock(&rules->mutex);
}

void	*do_something(t_philo_b *ph)
{
	sem_wait(&ph->rules->semaphore);
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	pthread_mutex_lock(&ph->rules->mutex);
	while (!ph->rules->exit_all)
	{
		pthread_mutex_unlock(&ph->rules->mutex);
		ph_think(ph);
		pthread_mutex_lock(&ph->rules->mutex);
	}
	pthread_mutex_unlock(&ph->rules->mutex);
	return (ptr);
}

t_philo	*create_phils(t_rules_b *rules)
{
	unsigned int	i;
	t_philo_b		*ph;
	pid_t			pid;

	ph = malloc(sizeof(t_philo) * rules->num_phil);
	i = 0;
	while (i < rules->num_phil)
	{
		ph[i].rules = rules;
		ph[i].id = i + 1;
		ph[i].meals = 0;
		pid = fork();
		if (pid != 0)
			break ;
		i++;
	}
	if (pid == 0)
	{
		i = 0;
		while (i < rules->num_phil)
			waitpid(ph[i++].process, NULL, 0);
	}
	else
	{
		ph[i].process = pid;
		do_something(&ph[i]);
	}
	return (ph);
}

void	init_table(t_rules_b	*rules)
{
	rules->exit_all = 0;
	rules->semaphore = sem_open("sem", O_CREAT, 0600);
	rules->forks = rules->num_phil;
	rules->ready = 0;
}

int	main(int argc, char **argv)
{
	int				i;
	t_rules_b		rules;
	t_philo			*ph;

	debugfd = open("_debug", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	parse_args(argc, argv, &rules);
	init_table(&rules);
	pids = malloc(sizeof(pthread_t) * rules.num_phil);
	ph = create_phils(&rules, pids);
	
	pthread_mutex_destroy(&rules.mutex);
	free (ph);
	free(tid);
	free(rules.forks);
	dprintf(debugfd, "End of program.\n");
	return (0);
}
