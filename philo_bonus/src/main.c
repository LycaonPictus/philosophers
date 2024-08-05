/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 14:03:35 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"
// gcc -I ../inc main.c table.c philosophers.c ph_think.c ph_eat.c ph_sleep.c check_ending.c parse_args.c timereg.c ../lib/*/*.c
void	unlink_semaphores(t_rules *rules, int start)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/other");
	if (!start)
	{
		sem_close(rules->fork_sem);
		sem_close(rules->print_sem);
		sem_close(rules->other_sem);
	}
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	int				result;

	unlink_semaphores(&rules, 1);
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	result = create_philos(&rules);
	if (!result)
		unlink_semaphores(&rules, 0);
	return (result);
}
