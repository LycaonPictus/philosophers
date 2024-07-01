/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 23:32:52 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	do_something(t_philo_b *ph)
{
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

pid_t	create_phils(t_rules_b *rules, t_philo_b **ph_ptr)
{
	unsigned int	i;
	t_philo_b		*ph;
	pid_t			pid;

	ph = malloc(sizeof(t_philo_b) * rules->num_phil);
	*ph_ptr = ph;
	i = 0;
	while (i < rules->num_phil)
	{
		ph[i].rules = rules;
		ph[i].id = i + 1;
		ph[i].meals = 0;
		ph[i].fork_sem = sem_open("/forks", O_CREAT, 0600, rules->num_phil / 2);
		pid = fork();
		if (pid)
			ph[i].proccess = pid;
		else
		{
			sem_wait(rules->semaphore);
			do_something(&ph[i]);
			sem_close(rules->semaphore);
			sem_close(ph->fork_sem);
			sem_unlink("/sem");
			sem_unlink("/forks");
			return (pid);
		}
		i++;
	}
	return (pid);
}

void	init_table(t_rules_b *rules)
{
	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->forks = rules->num_phil;
	rules->ready = 0;
	rules->semaphore = sem_open("/sem", O_CREAT, 0600, 0);
	rules->start_time = current_time(rules);
}

int	main(int argc, char **argv)
{
	t_rules_b		rules;
	t_philo_b		*ph;
	pid_t			pid;
	int				i;

	parse_args(argc, argv, &rules);
	init_table(&rules);
	pid = create_phils(&rules, &ph);
	if (!pid)
	{
		sem_close(rules.semaphore);
		return (0);
	}
	sem_post(rules.semaphore);
	i = 0;
	while (i < rules.num_phil)
		waitpid(ph[i++].proccess, NULL, 0);
	free(ph);
	sem_close(rules.semaphore);
	sem_unlink("/sem");
	return (0);
}
