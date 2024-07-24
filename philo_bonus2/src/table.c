/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:06:04 by jholland          #+#    #+#             */
/*   Updated: 2024/07/24 20:10:46 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	init_table(t_rules *rules)
{
	rules->exit_all = 0;
	rules->completed_goals = 0;
	rules->fork_sem = sem_open("forks", O_CREAT, 0600, rules->num_phil / 2);
	rules->print_sem = sem_open("print", O_CREAT, 0600, 1);
	rules->other_sem = sem_open("other", O_CREAT, 0600, 1);
	
}
