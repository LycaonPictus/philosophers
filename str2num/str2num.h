#ifndef STR2NUM_H
# define STR2NUM_H

typedef enum	e_str2num_status
{
	OK,
	NULLSTR,
	OVERFLOW,
	NAN
}	t_str2num_status;

int					str2int(char *str, t_str2num_status *error);
long				str2long(char *str, t_str2num_status *error);
long long			str2llong(char *str, t_str2num_status *error);
unsigned int		str2uint(char *str, t_str2num_status *error);
unsigned long		str2ulong(char *str, t_str2num_status *error);
unsigned long long	str2ullong(char *str, t_str2num_status *error);

#endif