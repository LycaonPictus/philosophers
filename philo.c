/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/06/19 22:56:52 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	debugfd;

void	exit_fn(int code, char *message)
{
	if (message)
		ft_putstr_fd(message, debugfd);
	close(debugfd);
	exit(code);
}

void	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		print_bad_args(argv[0]);
		exit_fn(1, NULL);
	}
}

void	*do_something(void *ptr)
{
	dprintf(debugfd, "I'm doing something with this pointer (%p)\n", ptr);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	a;

	debugfd = open("_debug", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	check_args(argc, argv);
	set_time(&table.start_time);
	pthread_create(&a, NULL, do_something, (void *)&table);
	pthread_join(a, NULL);
	exit_fn(0, "End of program.\n");
	return (0);
}
