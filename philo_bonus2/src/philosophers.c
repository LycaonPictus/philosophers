/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:04:28 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 21:10:18 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

int	start_action(t_philo *ph)
{
	return (ph_think(ph));
}

void	init_philo(t_philo *ph)
{
	ph->fork_sem = sem_open("/forks", O_CREAT);
	ph->print_sem = sem_open("/print", O_CREAT);
	ph->other_sem = sem_open("/other", O_CREAT);
	if (!ph->fork_sem || !ph->print_sem || !ph->other_sem)
	{
		sem_wait(ph->print_sem);
		write(2, "Sem error.\n", 11);
		sem_post(ph->print_sem);
		return ;
	}
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
}

void	set_attributes(t_philo *ph, unsigned int index)
{
	t_rules	*rules;

	rules = ph->rules;
	ph->id = index + 1;
	ph->meals = 0;
}

int	create_philos(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;
	pid_t			pid;
	int				action_result;
	int				catched_result;

	ph = malloc(sizeof(t_philo) * rules->num_phil);
	if (!ph)
		return (0);
	i = 0;
	while (i < rules->num_phil)
	{
		ph[i].rules = rules;
		set_attributes(&ph[i], i);
		pid = fork();
		if (pid)
			ph[i].pid = pid;
		else
		{
			init_philo(&ph[i]);
			while (1)
			{
				action_result = start_action(&ph[i]);
				if (action_result)
					break ;
			}
			free(ph);
			return (action_result);
		}
		i++;
	}
	sem_post(rules->other_sem);
	i = 0;
	while (i < rules->num_phil)
	{
		waitpid(-1, &catched_result, 0);
		catched_result = WEXITSTATUS(catched_result);
		sem_wait(rules->print_sem);
		printf("\tEVENT CATCHED (%i)\n", catched_result);
		sem_post(rules->print_sem);
		if (catched_result == 1)
		{
			i = 0;
			while (i < rules->num_phil)
			{
				sem_wait(rules->print_sem);
				printf("Killing philosopher %i\n", ph[i].id);
				sem_post(rules->print_sem);
				kill(ph[i++].pid, SIGKILL);
			}
			free(ph);
			return (0);
		}
		if (catched_result == 2)
			rules->completed_goals++;
		if (rules->num_meals && rules->completed_goals == rules->num_meals)
		{
			sem_wait(rules->print_sem);
			printf(" All philosophers have eaten %i times.\n", rules->num_meals);
			sem_post(rules->print_sem);
			return (0);
		}
		i++;
	}
	return (0);
}
