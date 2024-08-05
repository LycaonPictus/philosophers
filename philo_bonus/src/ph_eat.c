/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:05:07 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 21:24:46 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static int	end_and_sleep(t_philo *ph)
{
	int	sleep_return;

	sem_post(ph->fork_sem);
	if (ph->rules->num_meals)
		ph->meals++;
	sem_wait(ph->print_sem);
	printf("%i %i is sleeping\n",
		delta_time(ph->rules->start_time, current_time()), ph->id);
	sem_post(ph->print_sem);
	if (ph->rules->num_meals && ph->meals == ph->rules->num_meals)
		return (2);
	sleep_return = ph_sleep(ph);
	if (sleep_return == 1)
		return (1);
	return (0);
}

int	ph_eat(t_philo *ph)
{
	unsigned int	time_eating;
	int				check_result;
	int				eat_result;

	check_result = check_ending(ph, ph->rules);
	if (check_result)
		return (check_result);
	set_time(&ph->last_food);
	time_eating = delta_time(ph->last_thinking, ph->last_food);
	if (time_eating < ph->rules->time_to_eat)
	{
		usleep(10);
		eat_result = ph_eat(ph);
		return (eat_result);
	}
	else
		return (end_and_sleep(ph));
}
