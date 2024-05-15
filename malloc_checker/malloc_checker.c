/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:29 by jholland          #+#    #+#             */
/*   Updated: 2024/05/15 22:29:52 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_checker.h"
#include <stdlib.h>
#include <stdio.h>

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
				free(node->ptr);
				node->freed = 1;
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
		add_node(list, ptr, ptr ? "???" : "SAFE FREE");
	else
		add_node(list, ptr, "SAFE FREE");
}

void	clear_alloc_list(t_memlist **list)
{
	t_memlist	*node;
	t_memlist	*next;

	node = *list;
	if (!node)
		return ;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	*list = NULL;
}
