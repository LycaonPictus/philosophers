/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:06:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 19:40:38 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

static int	init_semaphores(t_rules *rules)
{
	rules->fork_sem = sem_open("/forks", O_CREAT, 0600, rules->num_phil / 2);
	if (rules->fork_sem == SEM_FAILED)
	{
		write(2, "Sem error.\n", 11);
		return (1);
	}
	rules->print_sem = sem_open("/print", O_CREAT, 0600, 1);
	if (rules->print_sem == SEM_FAILED)
	{
		write(2, "Sem error.\n", 11);
		sem_close(rules->fork_sem);
		sem_unlink("/forks");
		return (1);
	}
	rules->other_sem = sem_open("/other", O_CREAT, 0600, 0);
	if (rules->other_sem == SEM_FAILED)
	{
		write(2, "Sem error.\n", 11);
		sem_close(rules->fork_sem);
		sem_unlink("/forks");
		sem_close(rules->print_sem);
		sem_unlink("/print");
		return (1);
	}
	return (0);
}

int	init_table(t_rules *rules)
{
	rules->completed_goals = 0;
	if (init_semaphores(rules))
		return (1);
	if (set_time(&rules->start_time))
		return (1);
	return (0);
}
