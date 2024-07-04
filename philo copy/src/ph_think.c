/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:27:05 by jholland          #+#    #+#             */
/*   Updated: 2024/07/04 21:28:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	start_eating(t_philo *ph, struct timeval *now)
{
	ph->last_thinking = *now;
	ph->last_food = *now;
	printf("%i %i is eating\n",
		delta_time(ph->rules->start_time, *now) / 1000, ph->id);
}

static void	ph_take_fork(t_philo *ph, int *fork_ptr)
{
	struct timeval	now;

	now = current_time(ph->rules);
	if (fork_ptr != ph->left_fork && fork_ptr != ph->right_fork)
		return ;
	if (fork_ptr == ph->left_fork && *fork_ptr == 0)
		*(ph->left_fork) = 2;
	else if (fork_ptr == ph->right_fork && *fork_ptr == 0)
		*(ph->right_fork) = 1;
	else
		return ;
	printf("%i %i has taken a fork\n",
		delta_time(ph->rules->start_time, now) / 1000, ph->id);
}

static int	take_available_forks(t_philo *ph)
{
	struct timeval	now;

	now = current_time(ph->rules);
	if (*(ph->left_fork) == 0 && *(ph->right_fork) == 0)
	{
		ph_take_fork(ph, ph->left_fork);
		ph_take_fork(ph, ph->right_fork);
	}
	else if (*(ph->left_fork) == 0)
		ph_take_fork(ph, ph->left_fork);
	else if (*(ph->right_fork) == 0)
		ph_take_fork(ph, ph->right_fork);
	if (*(ph->left_fork) == 2 && *(ph->right_fork) == 1)
	{
		start_eating(ph, &now);
		return (1);
	}
	else
		return (0);
}

int	ph_think(t_philo *ph)
{
	if (check_ending(ph))
		return (0);
	return (!take_available_forks(ph));
}
