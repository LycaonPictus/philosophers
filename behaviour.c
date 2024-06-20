/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaviour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 23:34:45 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/philo.h"


static void	ph_sleep(t_philo *ph)
{
	int				time_no_eating;

	if (!ph->rules->phil_ok)
		return ;
	set_time(&(ph->rules->current_time));
	time_no_eating = (ph->rules->current_time.tv_sec - ph->last_food.tv_sec) * 1000 + (ph->rules->current_time.tv_usec - ph->last_food.tv_usec) / 1000;
	if (time_no_eating >= ph->rules->time_to_die)
	{
		printf("Philosopher %i dies while sleeping... (He ate %u meals)\n", ph->id, ph->meals);
		ph->rules->phil_ok = 0;
		return ;
	}
	if (time_no_eating >= ph->rules->time_to_sleep)
	{
		printf("Philosopher %i wakes up and starts thinking...\n", ph->id);
		ph_think(ph);
	}
	else
		ph_sleep(ph);
}

static void	ph_eat(t_philo *ph)
{
	if (!ph->rules->phil_ok)
		return ;
	*ph->left_fork = 0;
	*ph->right_fork = 0;
	ph->meals++;
	printf("Philosopher %i ñam, ñam...\n", ph->id);
	usleep(1000 * ph->rules->time_to_eat);
	set_time(&(ph->last_food));
	*ph->left_fork = 1;
	*ph->right_fork = 1;
	printf("Philosopher %i full, he feels sleepy...\n", ph->id);
	ph_sleep(ph);
}

void	ph_think(t_philo *ph)
{
	int	time_hungry;

	if (!ph->rules->phil_ok)
		return ;
	if (ph->left_fork != ph->right_fork && *ph->left_fork && *ph->right_fork)
	{
		ph_eat(ph);
		return ;
	}
	else
	{
		set_time(&ph->rules->current_time);
		time_hungry = (ph->rules->current_time.tv_sec - ph->last_food.tv_sec) * 1000 + (ph->rules->current_time.tv_usec - ph->last_food.tv_usec) / 1000;
		if (time_hungry >= ph->rules->time_to_die)
		{
			printf("Philosopher %i dies while thinking... (He ate %u meals)\n", ph->id, ph->meals);
			ph->rules->phil_ok = 0;
			return ;
		}
		usleep(1000000);
		ph_think(ph);
	}
}