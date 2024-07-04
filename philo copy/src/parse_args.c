/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:47:42 by jholland          #+#    #+#             */
/*   Updated: 2024/07/04 21:20:07 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/str2num.h"
#include "../inc/philo.h"

static void	print_bad_args(char *prog_name)
{
	write(2, "usage: \"", 8);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, " number_of_philosophers time_to_die time_to_eat time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]\"\n", 107);
	exit(1);
}

static int	parse_uint(char *arg, unsigned int *ptr)
{
	t_str2num_status	err;

	*ptr = str2uint(arg, &err);
	if (err == OK && *ptr != 0)
		return (0);
	write(2, "Parsing error: \"", 16);
	write(2, arg, ft_strlen(arg));
	write(2, "\" ", 2);
	if (err == NAN || (err == OK && *ptr == 0))
		write(2, "is not a positive number.\n", 26);
	else if (err == OVERFLOW)
		write(2, "overflows.\n", 11);
	else if (err == EMPTYSTR)
		write(2, "is an empty string.\n", 20);
	return (-1);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		print_bad_args(argv[0]);
		return (-1);
	}
	if (parse_uint(argv[1], &rules->num_phil)
		|| parse_uint(argv[2], &rules->time_to_die)
		|| parse_uint(argv[3], &rules->time_to_eat)
		|| parse_uint(argv[4], &rules->time_to_sleep))
		return (-1);
	rules->time_to_die *= 1000;
	rules->time_to_eat *= 1000;
	rules->time_to_sleep *= 1000;
	if (rules->time_to_sleep >= rules->time_to_die)
		rules->min_time = rules->time_to_die;
	else
		rules->min_time = rules->time_to_sleep;
	if (rules->time_to_eat < rules->min_time)
		rules->min_time = rules->time_to_eat;
	if (argc == 6 && parse_uint(argv[5], &rules->num_meals))
		return (-1);
	else
		rules->num_meals = 0;
	return (0);
}
