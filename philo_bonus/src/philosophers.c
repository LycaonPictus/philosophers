/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:04:28 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 15:31:59 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	init_philo(t_philo *ph)
{
	ph->fork_sem = sem_open("/forks", O_CREAT, 0600, ph->rules->num_phil / 2);
	ph->print_sem = sem_open("/print", O_CREAT, 0600, 1);
	if (!ph->fork_sem || !ph->print_sem)
	{
		write(2, "Sem error.\n", 11);
		return ;
	}
}

void	set_attributes(t_philo *ph, unsigned int index)
{
	ph->id = index + 1;
	ph->meals = 0;
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
}

/* int	child(t_philo *ph, unsigned int i)
{
	
} */

int	create_philos(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;
	pid_t			pid;
	int				action_result;
	int				catched_result;

	ph = malloc(sizeof(t_philo) * rules->num_phil);
	if (!ph)
		return (1);
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
				action_result = ph_think(&ph[i]);
				if (action_result)
					break ;
				usleep(10);
			}
			sem_close(ph[i].fork_sem);
			sem_close(ph[i].print_sem);
			free(ph);
			return (action_result);
		}
		i++;
	}
	i = 0;
	while (i < rules->num_phil)
	{
		waitpid(-1, &catched_result, 0);
		catched_result = WEXITSTATUS(catched_result);
		if (catched_result == 1)
		{
			i = 0;
			while (i < rules->num_phil)
				kill(ph[i++].pid, SIGKILL);
			sem_post(rules->print_sem);
			free(ph);
			return (0);
		}
		else if (catched_result == 2)
			rules->completed_goals++;
		if (rules->num_meals && rules->completed_goals == rules->num_phil)
		{
			sem_wait(rules->print_sem);
			printf("- All philosophers have eaten %i times -\n", rules->num_meals);
			sem_post(rules->print_sem);
			free(ph);
			return (0);
		}
		i++;
	}
	return (0);
}
