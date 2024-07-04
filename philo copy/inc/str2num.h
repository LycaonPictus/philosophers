/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2num.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:13:26 by jholland          #+#    #+#             */
/*   Updated: 2024/07/04 20:49:03 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR2NUM_H
# define STR2NUM_H

typedef enum e_str2num_status
{
	OK,
	NULLSTR,
	EMPTYSTR,
	OVERFLOW,
	NAN
}	t_str2num_status;

unsigned int	str2uint(char *str, t_str2num_status *error);

#endif