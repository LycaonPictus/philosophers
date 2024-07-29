/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:12:23 by jholland          #+#    #+#             */
/*   Updated: 2024/07/29 19:25:51 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <philo_bonus.h>*/#include "../inc/philo_bonus.h"

void	free4(void *p1, void *p2, void *p3, void *p4)
{
	free(p1);
	free(p2);
	free(p3);
	free(p4);
}
