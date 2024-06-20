/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 16:51:45 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	debugfd;

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
	parse_args(argc, argv, &rules);
	if (pthread_create(&a, NULL, do_something, NULL))
		exit_fn(1, "Error: pthread failure.\n");
	pthread_join(a, NULL);
	set_time(&rules.start_time);
	exit_fn(0, "End of program.\n");
	return (0);
}
