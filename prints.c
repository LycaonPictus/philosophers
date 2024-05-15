/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:34:59 by jholland          #+#    #+#             */
/*   Updated: 2024/05/03 14:51:47 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_bad_args(char *prog_name)
{
	write(2, "usage: ", 7);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, " number_of_philosophers time_to_die time_to_eat time_to_sleep "
	"[number_of_times_each_philosopher_must_eat]\n", 106);
	exit(1);
}