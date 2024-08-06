/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/06 20:41:22 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	{
		free(rules.forks);
		free(rules.fork_mutex);
		return (1);
	}
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	destroy_mutexes(&rules, rules.num_phil);
	free(ph);
	free(rules.forks);
	free(rules.fork_mutex);
	return (0);
}
