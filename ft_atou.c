/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jholland <jholland@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:31:32 by jholland          #+#    #+#             */
/*   Updated: 2024/05/05 02:19:41 by jholland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	add_cipher_uint(int *n, char cipher, int *error)
{
	unsigned int	i;
	unsigned int	result;

	i = 0;
	result = *n;
	while (i < 9)
	{
		result += *n;
		if (error && result < *n)
			*error = 1;
		i++;
	}
	result += cipher - '0';
	if (error && result < *n)
		*error = 1;
	*n = result;
}

int	ft_atou(char *str, int *error)
{
	int	n;

	if (error)
		*error = 0;
	if (!str)
	{
		*error = 3;
		return (0);
	}
	while (*str == ' ')
		str++;
	if (*str == '+')
		str++;
	n = 0;
	while (*str >= '0' && *str <= '9')
		add_cipher_uint(&n, *(str++), error);
	check_nan(str, error);
	return (n);
}
