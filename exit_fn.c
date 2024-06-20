/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:51:48 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 22:46:40 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"
extern int	debugfd;

void	exit_fn(int code, char *message)
{
	if (message)
		dprintf(debugfd, "%s\n", message);
	dprintf(debugfd, "Exit with code %i.\n", code);
	close(debugfd);
	exit(code); //Quitar
	
	//valgrind --tool=helgrind -s ./philo 5 400 200 200
}
