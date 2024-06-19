NAME = philo
SRC = philo.c prints.c timereg.c
OBJ = $(SRC:.c=.o)
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(SRC)
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(SRC) libft/*.c

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus
