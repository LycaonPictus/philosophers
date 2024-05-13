/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:18:43 by jholland          #+#    #+#             */
/*   Updated: 2024/05/13 17:14:19 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

typedef struct s_allocations
{
	void					*ptr;
	unsigned int			size;
	struct s_allocations	*next;
	int						freed;
	const char				*comment;
}	t_allocations;

int	log_fd;
t_allocations *alloc_list = NULL;

void	*mymalloc(t_allocations **list, unsigned int size, const char *comment);
void	myfree(t_allocations *list, void *ptr);
#endif