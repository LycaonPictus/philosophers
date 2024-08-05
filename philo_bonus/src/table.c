/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:06:04 by jholland          #+#    #+#             */
/*   Updated: 2024/08/05 20:12:44 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	init_table(t_rules *rules)
{
	rules->completed_goals = 0;
	rules->print_sem = sem_open("/print", O_CREAT, 0600, 1);
	return (0);
}
