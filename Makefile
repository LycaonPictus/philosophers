NAME = philo
SRC_FILES = philo.c prints.c timereg.c parse_args.c exit_fn.c ph_eat.c ph_sleep.c ph_think.c check_deaths.c
SRC_FOLDER = $(addprefix src/,$(SRC_FILES))
OBJ = $(addprefix obj/,$(SRC_FILES)) #$(SRC_FOLDER:.c=.o)
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(SRC_FOLDER)
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(SRC_FOLDER) libft/*.c str2num/str2ushort.c

clean:
	@rm -rf $(OBJ)
	@rm -rf _debug

fclean: clean
	@rm $(NAME)

re: fclean all

bonus:

.PHONY: all clean fclean re bonus
