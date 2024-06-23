/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/06/23 02:12:34 by jholland         ###   ########.fr       */
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
# include "str2num.h"
# include "../libft/libft.h" //
// Quitar dprintf

extern int	debugfd;

typedef struct s_rules
{
	struct timeval	current_time;
	unsigned short	num_phil;
	unsigned short	time_to_die;
	unsigned short	time_to_eat;
	unsigned short	time_to_sleep;
	unsigned short	first_event_time;
	unsigned short	num_meals;
	int				*forks;
	int				phil_ok;
}	t_rules;

typedef struct s_philo
{
	unsigned int	id;
	t_rules			*rules;
	int				*left_fork;
	int				*right_fork;
	struct timeval	last_thinking;
	struct timeval	last_food;
	unsigned int	meals;
}	t_philo;

unsigned int	ft_strlen(char *str);

void			parse_args(int argc, char **argv, t_rules *rules);
void			set_time(struct timeval *time);
void			print_bad_args(char *prog_name);
void			exit_fn(int code, char *message);
void			ph_think(t_philo *ph);

#endif