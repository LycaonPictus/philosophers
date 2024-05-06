NAME = philo
SRC = philo.c prints.c ft_strlen.c
OBJ = $(SRC:.c=.o)
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra


all: $(NAME)

$(NAME):
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(SRC)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus
