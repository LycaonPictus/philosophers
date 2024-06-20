/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 15:30:15 by jholland         ###   ########.fr       */
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
#include "str2num.h"
#include "../libft/libft.h" //

extern int	debugfd;

unsigned int	ft_strlen(char *str);

int		set_time(struct timeval *time);
void	print_bad_args(char *prog_name);

typedef struct s_rules
{
	struct timeval	start_time;
	unsigned short	num_phil;
	unsigned short	time_to_die;
	unsigned short	time_to_eat;
	unsigned short	time_to_sleep;
	unsigned short	num_meals;
}	t_rules;

typedef struct s_philo
{
	
}	t_philo;

#endif