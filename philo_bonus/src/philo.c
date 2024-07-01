/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 04:31:10 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int debugfd;

void	do_something(t_philo_b *ph)
{
	sem_wait(ph->rules->semaphore);
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	sem_post(ph->rules->semaphore);
	sem_wait(ph->rules->semaphore);
	while (!ph->rules->exit_all)
	{
		sem_post(ph->rules->semaphore);
		ph_think(ph);
		sem_wait(ph->rules->semaphore);
	}
	sem_post(ph->rules->semaphore);
}

t_philo_b	*create_phils(t_rules_b *rules)
{
	unsigned int	i;
	t_philo_b		*ph;
	pid_t			pid;

	ph = malloc(sizeof(t_philo_b) * rules->num_phil);
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
		set_time(&rules->start_time);
		sem_post(rules->semaphore);
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
	int	i;

	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->semaphore = sem_open("sem", O_CREAT, 0600);
	rules->fork_sem = sem_open("forks", O_CREAT, 0600);
	rules->forks = rules->num_phil;
	rules->ready = 0;
	i = 1;
	while (i < rules->num_phil)
	{
		sem_post(rules->fork_sem);
		i += 2;
	}
}

int	main(int argc, char **argv)
{
	t_rules_b		rules;
	t_philo_b		*ph;

	debugfd = open("_debug", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	parse_args(argc, argv, &rules);
	init_table(&rules);
	ph = create_phils(&rules);
	free(ph);
	dprintf(debugfd, "End of program.\n");
	return (0);
}
