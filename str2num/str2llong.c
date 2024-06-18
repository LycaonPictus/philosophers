#include "str2num.h"

static void	skip_spaces(char **ptr)
{
	char	*str;
	char	c;

	str = *ptr;
	c = *str;
	while (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f')
	{
		str++;
		c = *str;
	}
	*ptr = str;
}

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

static void	check_nan(char *str, t_str2num_status *error)
{
	if (error && *str)
		*error = NAN;
}

static void	check_llong_overflow(long long orig, long long new, t_str2num_status *error)
{
	if (error && *error == OK && ((orig < 0 && new > 0) || (orig > 0 && new < 0)))
		*error = OVERFLOW;
}

static void	add_cipher_llong(long long *ptr, char cipher, int sign, t_str2num_status *error)
{
	long long		number;
	long long		result;
	unsigned int	i;

	i = 0;
	number = *ptr;
	result = number;
	while (i < 9)
	{
		result += number;
		check_llong_overflow(number, result, error);
		i++;
	}
	result += sign * (cipher - '0');
	check_llong_overflow(number, result, error);
	*ptr = result;
}

long long	str2llong(char *str, t_str2num_status *error)
{
	long long	output;
	int			sign;

	if (error)
		*error = OK;
	if (!str)
	{
		if (error)
			*error = NULLSTR;
		return (0);
	}
	skip_spaces(&str);
	sign = get_sign(&str);
	output = 0;
	while (*str >= '0' && *str <= '9')
		add_cipher_llong(&output, *(str++), sign, error);
	skip_spaces(&str);
	check_nan(str, error);
	return (output);
}
