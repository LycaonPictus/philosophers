/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 20:48:37 by jholland         ###   ########.fr       */
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
	int				try_again;
}	t_philo;

unsigned int	ft_strlen(char *str);

int				parse_args(int argc, char **argv, t_rules *rules);
int				set_time(struct timeval *time);
void			print_bad_args(char *prog_name);
void			exit_fn(int code, char *message);
int				delta_time(struct timeval time1, struct timeval time2);
struct timeval	current_time(t_rules *rules);

int				check_ending(t_philo *ph);
void			ph_eat(t_philo *ph);
void			ph_think(t_philo *ph);
void			ph_sleep(t_philo *ph);

#endif