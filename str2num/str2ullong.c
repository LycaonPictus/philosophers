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

static void	skip_sign(char **str)
{
	if (**str == '+')
		(*str)++;
}

static void	check_nan(char *str, t_str2num_status *error)
{
	if (error && *str)
		*error = NAN;
}

static void	check_ullong_overflow(unsigned long long orig, unsigned long long new, t_str2num_status *error)
{
	if (error && (*error == OK) && (orig > new))
		*error = OVERFLOW;
}

static void	add_cipher_ullong(unsigned long long *ptr, char cipher, t_str2num_status *error)
{
	unsigned long long	number;
	unsigned long long	result;
	unsigned int		i;

	number = *ptr;
	result = number;
	i = 0;
	while (i < 9)
	{
		result += number;
		check_ullong_overflow(number, result, error);
		i++;
	}
	result += cipher - '0';
	check_ullong_overflow(number, result, error);
	*ptr = result;
}

unsigned long long	str2ullong(char *str, t_str2num_status *error)
{
	unsigned long long	output;

	if (error)
		*error = OK;
	if (!str)
	{
		if (error)
			*error = NULLSTR;
		return (0);
	}
	skip_spaces(&str);
	skip_sign(&str);
	output = 0;
	while (*str >= '0' && *str <= '9')
		add_cipher_ullong(&output, *(str++), error);
	skip_spaces(&str);
	check_nan(str, error);
	return (output);
}
