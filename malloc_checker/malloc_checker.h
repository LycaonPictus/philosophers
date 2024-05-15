/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:49:25 by jholland          #+#    #+#             */
/*   Updated: 2024/05/15 22:29:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_CHECKER_H
# define MALLOC_CHECKER_H


/**
 * @brief A list that stores the status of the allocation status of all
 * the pointers allocated or freed with the mymalloc and myfree functions,
 * including its size, memory direction, status, and custom hint comment
 * set when allocated.
 * @param ptr The direction of the allocated or freed pointer
 * @param size The size of the allocated memory
 * @param freed A status flag. 0 = Allocated by mymalloc but not freed,
 * 1 = Allocated by mymalloc and freed by myfree, 2 = Tried to double free,
 * -1 = Non-allocated by mymalloc
 * @param comment A custom hint message to improve the tracking
 */
typedef struct s_memlist
{
	void				*ptr;
	unsigned int		size;
	struct s_memlist	*next;
	int					freed;
	const char			*comment;
}	t_memlist;

/**
 * @brief This global pointer declaration has to exist and be initialized
 * at the beginning of the main file. And should be freed with clear_alloc_list
 * after printing it with print_allocs at the end of the main function.
 */
extern t_memlist	*g_alloc_list;

/**
 * @brief Allocates memory with malloc(size) and saves the reference in
 * a new last node of a list where it can be tracked using print_allocs
 * 
 * @param list Reference of the list in which the new pointer
 * will be attached
 * @param size Byte-size that will be allocatedd with malloc
 * @param comment Hint comment to display when tracking
 * @return void* 
 */
void	*mymalloc(t_memlist **list, unsigned int size, const char *comment);

/**
 * @brief Tries to free a memory allocation pointed by ptr made with
 * the mymalloc function. If it is registered as allocated, it normally
 * frees ptr. If is registered as already freed in its last ocurrence,
 * avoids freeing it will mark it as potential double free, without crashing.
 * If it was not previously registered, it regiters it as a try to free a
 * non-allocated memory, without crashing.
 * @param list Reference of the list in which ptr should be registered.
 * @param ptr The pointer which is tried to free.
 */
void	myfree(t_memlist **list, void *ptr);

/**
 * @brief Tracks the status of all memory allocation and freeings set
 * by the myalloc and myfree functions, including references, sizes
 * and hint comments.
 * You should avoid mixing myfree and my malloc with the original free
 * and malloc in order to avoid missing allocation tracking or false
 * free statuses.
 * Red statuses mean that at that point your project may have crashed
 * with the original free function. Yellow statuses mean that you should
 * look for memory leaks. Green statuses may not have to be reviewed.
 * @param list A pointer to the allocations list.
 */
void	print_allocs(t_memlist *list);

/**
 * @brief Clears the full list from the memory
 * 
 * @param list The reference to the list to be cleared
 */
void	clear_alloc_list(t_memlist **list);
#endif