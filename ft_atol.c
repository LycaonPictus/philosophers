/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:31:32 by jholland          #+#    #+#             */
/*   Updated: 2024/05/06 14:50:52 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_sign(char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

static void	check_nan(char *str, int *error)
{
	if (error)
		while (*str)
		{
			if (*str < '0' || *str > '9')
				*error = 2;
			str++;
		}
}

static void	add_cipher_int(long *n, char cipher, int sign, int *error)
{
	unsigned int	i;
	long			result;

	i = 0;
	result = *n;
	while (i < 9)
	{
		result += *n;
		if (error && ((sign < 0 && result > 0) || (sign > 0 && result < 0)))
			*error = 1;
		i++;
	}
	result += sign * (cipher - '0');
	if ((error && (*n < 0 && result > 0) || (*n > 0 && result < 0)))
		*error = 1;
	*n = result;
}

long	ft_atol(char *str, int *error)
{
	long	n;
	int		sign;

	if (error)
		*error = 0;
	if (!str)
	{
		*error = 3;
		return (0);
	}
	while (*str == ' ')
		str++;
	sign = get_sign(&str);
	n = 0;
	while (*str >= '0' && *str <= '9')
		add_cipher_int(&n, *(str++), sign, error);
	check_nan(str, error);
	return (n);
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	int error;
	if (argc == 2)
		printf("%li\n", ft_atol(argv[1], &error));
	printf("%i\n", error);
}