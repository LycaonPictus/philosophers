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

static void	check_int_overflow(int orig, int new, t_str2num_status *error)
{
	if (error && *error == OK && ((orig < 0 && new > 0) || (orig > 0 && new < 0)))
		*error = OVERFLOW;
}

static void	add_cipher_int(int *ptr, char cipher, int sign, t_str2num_status *error)
{
	int				number;
	int				result;
	unsigned int	i;

	number = *ptr;
	result = number;
	i = 0;
	while (i < 9)
	{
		result += number;
		check_int_overflow(number, result, error);
		i++;
	}
	result += sign * (cipher - '0');
	check_int_overflow(number, result, error);
	*ptr = result;
}

int	str2int(char *str, t_str2num_status *error)
{
	int	output;
	int	sign;

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
		add_cipher_int(&output, *(str++), sign, error);
	skip_spaces(&str);
	check_nan(str, error);
	return (output);
}
