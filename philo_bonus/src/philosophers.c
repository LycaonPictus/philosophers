/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:04:28 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 21:23:57 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	set_attributes(t_philo *ph, unsigned int index, t_rules *rules)
{
	ph->rules = rules;
	ph->id = index + 1;
	ph->meals = 0;
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	ph->print_sem = sem_open("/print", O_CREAT, 0600, 1);
	ph->fork_sem = sem_open("/forks", O_CREAT, 0600, ph->rules->num_phil / 2);
}

static int	philo_start(t_philo *ph, unsigned int i)
{
	int				action_result;

	while (1)
	{
		action_result = ph_think(&ph[i]);
		if (action_result)
			break ;
		usleep(10);
	}
	free(ph);
	return (action_result);
}

static void	wait_philos(t_philo *ph, t_rules *rules)
{
	unsigned int	i;
	int				catched_result;

	i = 0;
	while (i < rules->num_phil)
	{
		waitpid(-1, &catched_result, 0);
		catched_result = WEXITSTATUS(catched_result);
		if (catched_result == 1)
		{
			i = 0;
			while (i < rules->num_phil)
			{
				kill(ph[i].pid, SIGKILL);
				sem_close(ph[i].fork_sem);
				i++;
			}
			sem_post(rules->print_sem);
			free(ph);
			return ;
		}
		else if (catched_result == 2)
			rules->completed_goals++;
		if (rules->num_meals && rules->completed_goals == rules->num_phil)
		{
			sem_wait(rules->print_sem);
			printf("- All philosophers have eaten %i times -\n",
				rules->num_meals);
			sem_post(rules->print_sem);
			free(ph);
			return ;
		}
		i++;
	}
}

int	create_philos(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;
	pid_t			pid;

	if (set_time(&rules->start_time))
		return (1);
	ph = malloc(sizeof(t_philo) * rules->num_phil);
	if (!ph)
		return (1);
	i = 0;
	while (i < rules->num_phil)
	{
		set_attributes(&ph[i], i, rules);
		pid = fork();
		if (pid)
			ph[i].pid = pid;
		else
			return (philo_start(ph, i));
		i++;
	}
	wait_philos(ph, rules);
	sem_close(rules->print_sem);
	return (0);
}
