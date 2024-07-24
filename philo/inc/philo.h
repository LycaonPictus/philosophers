/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 17:58:02 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

# include "libft.h"

typedef struct s_rules
{
	struct timeval	start_time;
	unsigned short	num_phil;
	int				ready;
	unsigned short	time_to_die;
	unsigned short	time_to_eat;
	unsigned short	time_to_sleep;
	unsigned short	first_event_time;
	unsigned short	num_meals;
	unsigned short	completed_goals;
	int				*forks;
	pthread_mutex_t	*fork_mutex;
	int				exit_all;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
}	t_rules;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	t_rules			*rules;
	int				*left_fork;
	pthread_mutex_t	*left_fork_mutex;
	int				*right_fork;
	pthread_mutex_t	*right_fork_mutex;
	struct timeval	last_thinking;
	struct timeval	last_food;
	unsigned int	meals;
}	t_philo;

// PARSE FUNCTIONS
int				parse_args(int argc, char **argv, t_rules *rules);

// TIME FUNCTIONS
int				set_time(struct timeval *time);
struct timeval	current_time(t_rules *rules);
int				delta_time(struct timeval time1, struct timeval time2);

// TABLE
int				init_table(t_rules *rules);
void			destroy_mutexes(t_rules *rules, unsigned int n_forks);


// PHILOSPHER BEHAVIOUR
t_philo			*create_philos(t_rules *rules);
int				check_ending(t_philo *ph, t_rules *rules);
void			ph_eat(t_philo *ph);
void			ph_think(t_philo *ph);
void			ph_sleep(t_philo *ph);

// UTILS
void			free4(void *p1, void *p2, void *p3, void *p4);

#endif