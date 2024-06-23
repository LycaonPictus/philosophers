/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:47:42 by jholland          #+#    #+#             */
/*   Updated: 2024/06/23 01:31:51 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/str2num.h"
#include "inc/philo.h"

extern int	debugfd;

void	parse_ushort(char *arg, unsigned short *ptr)
{
	t_str2num_status	err;

	*ptr = str2ushort(arg, &err);
	dprintf(debugfd, "Parsed a number: %u (err = %i)\n", *ptr, err);
	if (err == OK && *ptr != 0)
		return ;
	write(2, "Parsing error: \"", 16);
	write(2, arg, ft_strlen(arg));
	write(2, "\" ", 2);
	if (err == NAN || *ptr == 0)
		write(2, "is not a positive number.\n", 26);
	else if (err == OVERFLOW)
		write(2, "overflows.\n", 11);
	else if (err == EMPTYSTR)
		write(2, "is an empty string.\n", 20);
	exit_fn(1, NULL);
}

void	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		print_bad_args(argv[0]);
		exit_fn(1, NULL);
	}
	parse_ushort(argv[1], &rules->num_phil);
	parse_ushort(argv[2], &rules->time_to_die);
	parse_ushort(argv[3], &rules->time_to_eat);
	parse_ushort(argv[4], &rules->time_to_sleep);
	if (rules->time_to_sleep >= rules->time_to_die)
		rules->first_event_time = rules->time_to_die;
	else
		rules->first_event_time = rules->time_to_sleep;
	if (argc == 6)
		parse_ushort(argv[5], &rules->num_meals);
	else
		rules->num_meals = 0;
}
