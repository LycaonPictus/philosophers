/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:29 by jholland          #+#    #+#             */
/*   Updated: 2024/05/14 23:32:07 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_checker.h"

static t_memlist	*add_node(t_memlist **list, void *ptr, const char *comment)
{
	t_memlist	*new;
	t_memlist	*node;

	new = malloc(sizeof(t_memlist));
	new->freed = -1;
	new->size = 0;
	new->ptr = ptr;
	new->comment = comment;
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
	return (new);
}

/**
 * @brief Allocates memory with malloc(size) and saves the reference in a new last node of a list where it can be tracked using print_allocs
 * 
 * @param list Reference of the list in which the new pointer will be attached
 * @param size Byte-size that will be allocatedd with malloc
 * @param comment Hint comment to display on tracking
 * @return void* 
 */
void	*mymalloc(t_memlist **list, unsigned int size, const char *comment)
{
	void		*ptr;
	t_memlist	*new;

	ptr = malloc(size);
	new = add_node(list, ptr, comment);
	new->size = size;
	new->ptr = malloc(size);
	new->comment = comment;
	new->freed = 0;
	return (new->ptr);
}

/**
 * @brief Tracks the status of all memory allocation and freeings set by the myalloc and my free functions, including references, sizes and hint comments
 * 
 * @param list 
 */
void	print_allocs(t_memlist *list)
{
	while (list)
	{
		if (list->freed == -1 && list->ptr)
			printf("\033[0;31m[NO_ALLOC]\033[0m\t");
		else if (list->freed == -1 && !list->ptr)
			printf("\033[0;32m[NLLFREED]\033[0m\t");
		else if (list->freed == 0)
			printf("\033[0;33m[MEM_LEAK]\033[0m\t");
		else if (list->freed == 1)
			printf("\033[0;32m[FREED_OK]\033[0m\t");
		else if (list->freed == 2)
			printf("\033[0;31m[DBL_FREE]\033[0m\t");
		printf("%-14p\t%3u bytes\t%s\n", list->ptr, list->size, list->comment);
		list = list->next;
	}
}

static void	free_ptr(t_memlist *node)
{
	free(node->ptr);
	node->freed = 1;
}

void	myfree(t_memlist **list, void *ptr)
{
	t_memlist	*last_freed;
	t_memlist	*node;

	last_freed = NULL;
	node = *list;
	while (node)
	{
		if (node->ptr == ptr)
		{
			if (node->freed == 0)
			{
				free_ptr(node);
				return ;
			}
			else if (node->freed == 1)
				last_freed = node;
		}
		node = node->next;
	}
	if (last_freed)
		last_freed->freed = 2;
	else if (ptr)
		add_node(list, ptr, "???");
	else
		add_node(list, ptr, "SAFE FREE");
}
