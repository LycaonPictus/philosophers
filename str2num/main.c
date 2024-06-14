

#include <stdio.h>
#include "str2num.h"

void	print_errors(t_str2num_status e)
{
	if (e == OK)
		printf("OK\n");
	if (e == NULLSTR)
		printf("NULLSTR\n");
	if (e == OVERFLOW)
		printf("OVERFLOW\n");
	if (e == NAN)
		printf("NAN\n");
}

int	main(int argc, char **argv)
{
	int					i = 1;
	t_str2num_status	e;

	while (i < argc)
	{
		printf("\tINT:\t%16i\t", ft_atoi(argv[i], &e));
		print_errors(e);
		printf("\tLONG:\t%16li\t", ft_atol(argv[i], &e));
		print_errors(e);
		printf("\tUINT:\t%16u\t", ft_atou(argv[i], &e));
		print_errors(e);
		i++;
	}
}