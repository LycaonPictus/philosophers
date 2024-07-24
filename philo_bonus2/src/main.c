/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 20:02:18 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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
		free4(rules.forks, rules.fork_mutex, NULL, NULL);
		return (1);
	}
	i = 0;
	while (i < rules.num_phil)
		pthread_join(ph[i++].thread, NULL);
	destroy_mutexes(&rules, rules.num_phil);
	free4(rules.forks, rules.fork_mutex, ph, NULL);
	return (0);
}
