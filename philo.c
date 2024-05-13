/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/05/13 17:15:02 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	/* int	time;
	log_fd = open("_log", O_WRONLY);
	if (argc < 5 || argc > 6)
		print_bad_args(argv[0]);
	
	struct timeval tv;
	time = gettimeofday(&tv, NULL);
	if (!time)
		printf("Exito, %lu\n", tv.tv_usec/1000);
	return (0); */
	printf("%p\n", mymalloc(&alloc_list, 3, "TEST"));
	close(log_fd);
}
