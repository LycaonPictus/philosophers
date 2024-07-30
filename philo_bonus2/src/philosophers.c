/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:04:28 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 00:43:48 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

/*void	start_action(t_philo *ph)
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
}*/
#include <stdio.h>
void	init_philo(t_philo *ph)
{
	ph->fork_sem = sem_open("/forks", O_CREAT);
	ph->print_sem = sem_open("/print", O_CREAT);
	ph->other_sem = sem_open("/other", O_CREAT);
	if (!ph->fork_sem || !ph->print_sem || !ph->other_sem)
	{
		sem_wait(ph->print_sem);
		write(2, "Sem error2.\n", 12);//
		sem_post(ph->print_sem);
		return ;
	}
	sem_wait(ph->other_sem);
	sem_wait(ph->print_sem);
	printf("Hola %i, %li\n", ph->id, ph->rules->start_time.tv_sec);
	sem_post(ph->print_sem);
	sem_post(ph->other_sem);
	return ;
	ph->last_food = ph->rules->start_time;
	ph->last_thinking = ph->rules->start_time;
	//start_action(ph);
}

void	set_attributes(t_philo *ph, unsigned int index)
{
	t_rules	*rules;

	rules = ph->rules;
	ph->id = index + 1;
	ph->meals = 0;
}

t_philo	*create_philos(t_rules *rules)
{
	unsigned int	i;
	t_philo			*ph;
	pid_t			pid;

	ph = malloc(sizeof(t_philo) * rules->num_phil);
	if (!ph)
		return (NULL);
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
			sem_wait(rules->print_sem);
			printf("Philo %i created\n", i + 1);
			sem_post(rules->print_sem);
			init_philo(&ph[i]);
			return (NULL);
		}
		i++;
	}
	sem_wait(rules->print_sem);
	printf("All philos created\n");
	sem_post(rules->print_sem);
	set_time(&rules->start_time);
	sem_post(rules->other_sem);
	return (ph);
	i = 0;
	while (i < rules->num_phil)
	{
		waitpid(ph[i++].pid, NULL, 0);
		sem_wait(rules->print_sem);
		printf("Philo %i finished\n", i);
		sem_post(rules->print_sem);
	}
}
