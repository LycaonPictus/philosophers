/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:47:42 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 14:21:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str2num.h>
#include <philo_bonus.h>

static void	print_bad_args(char *prog_name)
{
	write(2, "usage: \"", 8);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, " number_of_philosophers time_to_die time_to_eat time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]\"\n", 107);
	exit(1);
}

static int	parse_ushort(char *arg, unsigned short *ptr)
{
	t_str2num_status	err;

	*ptr = str2ushort(arg, &err);
	if (err == OK && *ptr != 0)
		return (0);
	write(2, "Parsing error: \"", 16);
	write(2, arg, ft_strlen(arg));
	write(2, "\" ", 2);
	if (err == NAN || *ptr == 0)
		write(2, "is not a positive number.\n", 26);
	else if (err == OVERFLOW)
		write(2, "overflows.\n", 11);
	else if (err == EMPTYSTR)
		write(2, "is an empty string.\n", 20);
	return (1);
}

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		print_bad_args(argv[0]);
		return (1);
	}
	if (parse_ushort(argv[1], &rules->num_phil)
		|| parse_ushort(argv[2], &rules->time_to_die)
		|| parse_ushort(argv[3], &rules->time_to_eat)
		|| parse_ushort(argv[4], &rules->time_to_sleep))
		return (1);
	rules->num_meals = 0;
	if (argc == 6 && parse_ushort(argv[5], &rules->num_meals))
		return (1);
	return (0);
}
