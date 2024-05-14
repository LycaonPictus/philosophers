/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:04 by jholland          #+#    #+#             */
/*   Updated: 2024/05/14 22:46:33 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_allocations *alloc_list = NULL;

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
	char *ptr = mymalloc(&alloc_list, 10, "Prueba de doble free");
	myfree(&alloc_list, ptr);
	myfree(&alloc_list, ptr);
	ptr = mymalloc(&alloc_list, 10, "Voy a perder esta referencia");
	ptr = mymalloc(&alloc_list, 10, "Guardando esta y la libero");
	myfree(&alloc_list, ptr);
	ptr = NULL;
	myfree(&alloc_list, ptr);
	myfree(&alloc_list, "Hola");
	myfree(&alloc_list, 0x0);

	print_allocs(alloc_list);
}
