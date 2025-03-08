NAME = pipex
CC = cc
FLAGS = -Werror -Wall -Wextra -g
DEBUG_FLAGS = -Wall -Wextra -g -fsanitize=address
### PATHS

P_LIB = libft/
P_SRC = src/
P_OBJ = .obj/

### FILES

SRC = parsing.c main.c execution.c arr_utils.c str_utils.c error.c
OBJ = $(addprefix $(P_OBJ), $(SRC:%.c=%.o))
HEADER = pipex.h

### RULES

.PHONY = all clean fclean re lib

all: lib $(NAME)

clean:
	$(MAKE) -C $(P_LIB) clean
	rm -rf $(P_OBJ)

fclean: clean
	$(MAKE) -C $(P_LIB) fclean
	rm -rf $(NAME)

re: fclean 
	$(MAKE) all

lib:
	$(MAKE) -C $(P_LIB) all

debug:
	$(MAKE) re FLAGS="$(DEBUG_FLAGS)"
	$(MAKE) clean

$(NAME): $(OBJ) $(P_LIB)libft.a
	$(CC) $(FLAGS) $(OBJ) -L$(P_LIB) -lft -o $@

$(P_LIB)libft.a:
	lib

$(P_OBJ):
	mkdir -p $(P_OBJ)

$(P_OBJ)%.o: $(P_SRC)%.c $(HEADER) | $(P_OBJ)
	$(CC) $(FLAGS) -c $< -I $(P_LIB) -I. -o $@
