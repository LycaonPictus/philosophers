/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 21:50:04 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	*check_exit(void *ptr)
{
	int				check_result;
	t_philo			*ph;
	struct timeval	time;

	time = current_time();
	ph = ptr;
	check_result = 0;
	while (!check_result
		&& delta_time(time, current_time()) < ph->rules->time_to_die + 1)
	{
		check_result = check_ending(ph, ph->rules);
		if (check_result)
			exit (check_result);
	}
	return (NULL);
}

int	ph_think(t_philo *ph)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, check_exit, ph);
	pthread_detach(thread);
	sem_wait(ph->fork_sem);
	set_time(&ph->last_thinking);
	sem_wait(ph->print_sem);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, ph->last_thinking), ph->id);
	sem_post(ph->print_sem);
	return (ph_eat(ph));
}
