/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/06/30 21:01:22 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <semaphore.h>
# include <sys/wait.h>

extern int	debugfd;

typedef struct s_rules_b
{
	struct timeval	start_time;
	unsigned short	num_phil;
	int				ready;
	unsigned short	time_to_die;
	unsigned short	time_to_eat;
	unsigned short	time_to_sleep;
	unsigned short	first_event_time;
	unsigned short	num_meals;
	int				forks;
	int				exit_all;
	sem_t       	*semaphore;
}	t_rules_b;

typedef struct s_philo_b
{
	unsigned int	id;
	pthread_t		process;
	t_rules_b		*rules;
	struct timeval	last_thinking;
	struct timeval	last_food;
	unsigned int	meals;
}	t_philo_b;

#endif