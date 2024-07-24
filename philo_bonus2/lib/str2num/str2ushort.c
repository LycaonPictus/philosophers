/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2ushort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:11:25 by jholland          #+#    #+#             */
/*   Updated: 2024/07/18 14:59:20 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <str2num.h>

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

static void	check_ushort_overflow(unsigned short orig, unsigned short new,
	t_str2num_status *error)
{
	if (error && (*error == OK) && (orig > new))
		*error = OVERFLOW;
}

static void	add_cipher_ushort(unsigned short *ptr, char cipher,
	t_str2num_status *error)
{
	unsigned short	number;
	unsigned short	result;
	unsigned short	i;

	number = *ptr;
	result = number;
	i = 0;
	while (i < 9)
	{
		result += number;
		check_ushort_overflow(number, result, error);
		i++;
	}
	result += cipher - '0';
	check_ushort_overflow(number, result, error);
	*ptr = result;
}

unsigned short	str2ushort(char *str, t_str2num_status *error)
{
	unsigned short	output;

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
		add_cipher_ushort(&output, *(str++), error);
	skip_spaces(&str);
	if (error && *str)
		*error = NAN;
	return (output);
}
