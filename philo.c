/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 16:22:18 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	debugfd;

void	exit_fn(int code, char *message)
{
	if (message)
		ft_putstr_fd(message, debugfd);
	dprintf(debugfd, "Exit with code %i.\n", code);
	close(debugfd);
	exit(code);
}

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
	if (err == NAN)
		write(2, "is not a number.\n", 17);
	else if (err == OVERFLOW)
		write(2, "overflows.\n", 11);
	else if (err == EMPTYSTR)
		write(2, "is an empty string.\n", 20);
	else if (*ptr == 0)
		write(2, "is not a valid value.\n", 22);
	exit_fn(1, NULL);
}

void	check_args(int argc, char **argv, t_rules *rules)
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
	if (argc == 6)
		parse_ushort(argv[5], &rules->num_meals);
	else
		rules->num_meals = 0;
}

void	*do_something(void *ptr)
{
	dprintf(debugfd, "I'm doing something\n");
	return (ptr);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	a;

	debugfd = open("_debug", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	check_args(argc, argv, &rules);
	if (pthread_create(&a, NULL, do_something, NULL))
		exit_fn(1, "Error: pthread failure.\n");
	pthread_join(a, NULL);
	set_time(&rules.start_time);
	exit_fn(0, "End of program.\n");
	return (0);
}
