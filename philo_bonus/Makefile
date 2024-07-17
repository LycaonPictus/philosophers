NAME = philo_bonus
SRC_FILES = philo.c prints.c timereg.c parse_args.c exit_fn.c ph_eat.c ph_sleep.c ph_think.c check_ending.c
SRC_FOLDER = $(addprefix src/,$(SRC_FILES))
OBJ = $(addprefix obj/,$(SRC_FILES)) #$(SRC_FOLDER:.c=.o)
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra -g#-fsanitize=address

all: $(NAME)

$(NAME): $(SRC_FOLDER)
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(SRC_FOLDER) ../philo/lib/libft/*.c ../philo/lib/str2num/str2ushort.c

clean:
	@rm -rf $(OBJ)
	@rm -rf _debug

fclean: clean
	@rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
