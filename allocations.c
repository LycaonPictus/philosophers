/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:29 by jholland          #+#    #+#             */
/*   Updated: 2024/05/13 16:18:49 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

extern int	log_fd;

void	*mymalloc(t_allocations **list, unsigned int size, const char *comment)
{
	void			*ptr;
	t_allocations	*new;
	t_allocations	*node;

	new = malloc(sizeof(t_allocations));
	new->size = size;
	new->ptr = malloc(size);
	new->comment = comment;
	new->freed = 0;
	new->next = NULL;
	if (!*list)
		(*list) = new;
	else
	{
		node = *list;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	return (new->ptr);
}

void	myfree(t_allocations *list, void *ptr)
{
	int	dbl_free = 0;

	while (list)
	{
		if (list->ptr == ptr)
			if (list->freed)
				dbl_free = 1;
			else
			{
				free(list->ptr);
				list->freed = 1;
				return ;
			}
		list = list->next;
	}
	if (dbl_free)
	{
		write(log_fd, ">> ERROR, TRIED TO DOUBLE FREE\n", 31);
		return ;
	}
	write(log_fd, ">> ERROR, TRIED TO FREE A NOT ALLOCATED POINTER\n", 48);
}
