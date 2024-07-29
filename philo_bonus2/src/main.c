/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/29 21:37:40 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"
// gcc -I ../inc main.c table.c philosophers.c parse_args.c timereg.c ../lib/*/*.c
int	main(int argc, char **argv)
{
	unsigned int	i;
	t_rules			rules;
	t_philo			*ph;

	ph = NULL;
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	ph = create_philos(&rules);
	if (!ph)
		return (0);
	sem_wait(rules.print_sem);
	printf("A");
	sem_post(rules.print_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/other");
	return (0);
	/* if (!ph)
	{
		free4(rules.forks, rules.fork_mutex, NULL, NULL);
		return (1);
	}
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	destroy_mutexes(&rules, rules.num_phil);
	free4(rules.forks, rules.fork_mutex, ph, NULL); */
	return (0);
}
