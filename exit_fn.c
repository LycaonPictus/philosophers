/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:51:48 by jholland          #+#    #+#             */
/*   Updated: 2024/06/20 16:52:21 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"
extern int	debugfd;

void	exit_fn(int code, char *message)
{
	if (message)
		ft_putstr_fd(message, debugfd);
	dprintf(debugfd, "Exit with code %i.\n", code);
	close(debugfd);
	exit(code);
}
