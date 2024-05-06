/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/05/03 15:58:49 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
int	main(int argc, char **argv)
{
	int	time;

	if (argc < 5 || argc > 6)
		print_bad_args(argv[0]);
	
	struct timeval tv;
	time = gettimeofday(&tv, NULL);
	if (!time)
		printf("Exito, %lu\n", tv.tv_usec/1000);
	return (0);
}
