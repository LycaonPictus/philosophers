NAME = philo
SRC = philo.c prints.c timereg.c parse_args.c exit_fn.c
OBJ = $(SRC:.c=.o)
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(SRC)
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(SRC) libft/*.c str2num/str2ushort.c

clean:
	@rm -rf $(OBJ)
	@rm -rf _debug

fclean: clean
	@rm $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus
