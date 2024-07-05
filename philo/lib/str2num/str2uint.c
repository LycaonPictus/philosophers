/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:11:25 by jholland          #+#    #+#             */
/*   Updated: 2024/07/04 20:48:22 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/str2num.h"

static void	skip_spaces(char **ptr)
{
	char	*str;
	char	c;

	str = *ptr;
	c = *str;
	while (c == ' ' || c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f')
	{
		str++;
		c = *str;
	}
	*ptr = str;
}

static void	check_uint_overflow(unsigned int orig, unsigned int new,
	t_str2num_status *error)
{
	if (error && (*error == OK) && (orig > new))
		*error = OVERFLOW;
}

static void	add_cipher_uint(unsigned int *ptr, char cipher,
	t_str2num_status *error)
{
	unsigned int	number;
	unsigned int	result;
	unsigned int	i;

	number = *ptr;
	result = number;
	i = 0;
	while (i < 9)
	{
		result += number;
		check_uint_overflow(number, result, error);
		i++;
	}
	result += cipher - '0';
	check_uint_overflow(number, result, error);
	*ptr = result;
}

unsigned int	str2uint(char *str, t_str2num_status *error)
{
	unsigned int	output;

	if (error)
		*error = OK;
	if (!str)
	{
		if (error)
			*error = NULLSTR;
		return (0);
	}
	skip_spaces(&str);
	if (!*str)
		*error = EMPTYSTR;
	if (*str == '+')
		str += 1;
	output = 0;
	while (*str >= '0' && *str <= '9')
		add_cipher_uint(&output, *(str++), error);
	skip_spaces(&str);
	if (error && *str)
		*error = NAN;
	return (output);
}
