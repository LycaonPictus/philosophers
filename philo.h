/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/06/19 18:59:05 by jholland         ###   ########.fr       */
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
#include "libft/libft.h" //

extern int	debugfd;

unsigned int	ft_strlen(char *str);

int		set_time(struct timeval *time);
void	print_bad_args(char *prog_name);

typedef struct s_table
{
	struct timeval	start_time;
}	t_table;

typedef struct s_philo
{
	
}	t_philo;

#endif