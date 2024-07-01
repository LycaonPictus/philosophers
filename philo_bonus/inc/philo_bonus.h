/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/07/01 04:26:01 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>
# include "../../philo/inc/libft.h"
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
	unsigned short	completed_goals;
	int				forks;
	int				exit_all;
	sem_t       	*semaphore;
	sem_t       	*fork_sem;
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

unsigned int	ft_strlen(char *str);

void			parse_args(int argc, char **argv, t_rules_b *rules);
int				set_time(struct timeval *time);
void			print_bad_args(char *prog_name);
void			exit_fn(int code, char *message);
int				delta_time(struct timeval time1, struct timeval time2);
struct timeval	current_time(t_rules_b *rules);

int				check_ending(t_philo_b *ph);
void			ph_eat(t_philo_b *ph);
void			ph_think(t_philo_b *ph);
void			ph_sleep(t_philo_b *ph);

#endif