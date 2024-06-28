/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:51:48 by jholland          #+#    #+#             */
/*   Updated: 2024/06/25 21:17:36 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

	//valgrind --tool=helgrind -s ./philo 5 400 200 200
void	exit_fn(int code, char *message)
{
	write(2, message, ft_strlen(message));
	exit(code); //Quitar	
}
