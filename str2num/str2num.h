#ifndef STR2NUM_H
# define STR2NUM_H

typedef enum    e_str2num_status
{
    OK,
    NULLSTR,
    OVERFLOW,
    NAN
}   t_str2num_status;

int             ft_atoi(char *str, t_str2num_status *error);
long            ft_atol(char *str, t_str2num_status *error);
unsigned int    ft_atou(char *str, t_str2num_status *error);

#endif