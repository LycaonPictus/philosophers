/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/30 20:15:05 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"
// gcc -I ../inc main.c table.c philosophers.c parse_args.c timereg.c ../lib/*/*.c
void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/other");
}

int	main(int argc, char **argv)
{
	unsigned int	i;
	t_rules			rules;
	int				result;

	unlink_semaphores();
	if (parse_args(argc, argv, &rules))
		return (1);
	if (init_table(&rules))
		return (1);
	result = create_philos(&rules);
	if (result)
	{
		sem_wait(rules.print_sem);
		printf("Philo finished with status %i\n", result);
		sem_post(rules.print_sem);
		return (result);
	}
	sem_wait(rules.print_sem);
	printf("Program finished\n");
	sem_post(rules.print_sem);
	unlink_semaphores();
	return (0);
}
