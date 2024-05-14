/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 23:09:47 by jholland          #+#    #+#             */
/*   Updated: 2024/05/14 23:14:53 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_checker.h"

t_memlist	*alloc_list = NULL;

int	main(int argc, char **argv)
{
	char	*ptr;

	ptr = mymalloc(&alloc_list, 10, "Prueba de doble free");
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
