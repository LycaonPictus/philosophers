

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
#include <limits.h>

int	main(int argc, char **argv)
{
	int					i = 1;
	t_str2num_status	e = OK;

	while (i < argc)
	{
		printf("\tINT:\t%16i\t", str2int(argv[i], &e));
		print_errors(e);
		printf("\tLONG:\t%16li\t", str2long(argv[i], &e));
		print_errors(e);
		printf("\tLLONG:\t%16lli\t", str2llong(argv[i], &e));
		print_errors(e);
		printf("\tUINT:\t%16u\t", str2uint(argv[i], &e));
		print_errors(e);
		printf("\tULONG:\t%16lu\t", str2ulong(argv[i], &e));
		print_errors(e);
		printf("\tULLONG:\t%16llu\t", str2ullong(argv[i], &e));
		print_errors(e);
		i++;
	}
}