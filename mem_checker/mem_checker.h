/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_checker.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:49:25 by jholland          #+#    #+#             */
/*   Updated: 2024/05/14 23:14:35 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_CHECKER_H
# define MEM_CHECKER_H
# include <stdlib.h>

# include <stdio.h>

typedef struct s_memlist
{
	void					*ptr;
	unsigned int			size;
	struct s_memlist		*next;
	int						freed;
	const char				*comment;
}	t_memlist;

extern t_memlist	*alloc_list;

void	*mymalloc(t_memlist **list, unsigned int size, const char *comment);
void	myfree(t_memlist **list, void *ptr);
void	print_allocs(t_memlist *list);

#endif