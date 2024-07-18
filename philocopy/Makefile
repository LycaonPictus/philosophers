NAME = philo
COMPILER = gcc
OPTIONS = -Wall -Werror -Wextra #-fsanitize=address
INCLUDES = -Iinc

SRC_DIR = src
SRC_FILES = main.c prints.c timereg.c parse_args.c ph_eat.c \
			ph_sleep.c ph_think.c check_ending.c
SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

LIBFT_DIR = lib/libft
LIBFT_FILES = ft_strlen.c
LIBFT = $(addprefix $(LIBFT_DIR)/,$(LIBFT_FILES))

STR2NUM_DIR = lib/str2num
STR2NUM_FILES = str2ushort.c
STR2NUM = $(addprefix $(STR2NUM_DIR)/,$(STR2NUM_FILES))

OBJ = $(SRC:%.c=%.o) $(STR2NUM:%.c=%.o) $(LIBFT:%.c=%.o)

all: $(NAME)

%.o: %.c
	@$(COMPILER) $(OPTIONS) -g -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	@$(COMPILER) $(OPTIONS) -o $(NAME) $(OBJ) $(INCLUDES)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
