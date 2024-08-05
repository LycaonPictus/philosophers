/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 21:14:36 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
}

int	main(int argc, char **argv)
{
	t_rules			rules;
	int				result;

	unlink_semaphores();
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	result = create_philos(&rules);
	sem_close(rules.print_sem);
	unlink_semaphores();
	return (result);
}
