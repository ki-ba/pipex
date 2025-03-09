NAME = pipex
CC = cc
FLAGS = -Werror -Wall -Wextra -g
DEBUG_FLAGS = -Wall -Wextra -g -fsanitize=address
BONUS_FLAGS = -DBONUS=1
### PATHS

P_LIB = libft/
P_SRC_MANDATORY = src/mandatory/
P_SRC_BONUS = src/bonus/
P_OBJ = .obj/
P_INC = inc/

### FILES

M_SRC = main.c parsing.c execution.c error.c
M_SRCPATH = $(addprefix $(P_SRC_MANDATORY), $(M_SRC)))

B_SRC = main_bonus.c parsing_bonus.c execution_bonus.c error_bonus.c
B_SRCPATH = $(addprefix $(P_SRC_MANDATORY), $(B_SRC)))

OBJ = $(addprefix $(P_OBJ), $(M_SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(P_OBJ), $(B_SRC:%.c=%.o))

HEADER = $(P_INC)pipex.h

### RULES

.PHONY = all clean fclean re lib bonus

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

bonus: $(BONUS_OBJ) $(P_LIB)libft.a
	$(CC) $(FLAGS) $(BONUS_OBJ) -L$(P_LIB) -lft -o $(NAME)

$(NAME): $(OBJ) $(P_LIB)libft.a
	$(CC) $(FLAGS) $(OBJ) -L$(P_LIB) -lft -o $@

$(P_LIB)libft.a:
	lib

$(P_OBJ):
	mkdir -p $(P_OBJ)

$(P_OBJ)%.o: $(SRCPATH)%.c $(HEADER) | $(P_OBJ)
	$(CC) $(FLAGS) -c $< -I $(P_LIB) -I. -o $@
