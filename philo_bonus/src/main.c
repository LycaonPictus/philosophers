/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 14:36:54 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	unlink_semaphores(t_rules *rules, int start)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	if (!start)
	{
		sem_close(rules->fork_sem);
		sem_close(rules->print_sem);
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
