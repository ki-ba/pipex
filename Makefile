NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
FLAGS = -Werror -Wall -Wextra -g
DEBUG_FLAGS = -Wall -Wextra -g -fsanitize=address
### PATHS

P_LIB = libft/
P_SRC_MANDATORY = src/mandatory/
P_SRC_BONUS = src/bonus/

P_BOBJ = .obj/bonus/
P_MOBJ = .obj/mandatory/
P_INC = inc/

B_HEADER= pipex_bonus.h
M_HEADER = pipex.h

### FILES

M_SRC = main.c parsing.c execution.c error.c
M_SRCPATH = $(addprefix $(P_SRC_MANDATORY), $(M_SRC)))

B_SRC = main_bonus.c parsing_bonus.c execution_bonus.c error_bonus.c
B_SRCPATH = $(addprefix $(P_SRC_MANDATORY), $(B_SRC)))

OBJ = $(addprefix $(P_MOBJ), $(M_SRC:%.c=%.o))
BONUS_OBJ = $(addprefix $(P_BOBJ), $(B_SRC:%.c=%.o))

HEADER = $(P_INC)pipex.h

### RULES

.PHONY = all clean fclean re lib bonus

all: lib $(NAME)

clean:
	$(MAKE) -C $(P_LIB) clean
	rm -rf $(P_MOBJ)* $(P_BOBJ)*

fclean: clean
	$(MAKE) -C $(P_LIB) fclean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean
	$(MAKE) all

lib:
	$(MAKE) -C $(P_LIB)

debug:
	$(MAKE) re FLAGS="$(DEBUG_FLAGS)"
	$(MAKE) clean

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(P_LIB)libft.a
	$(CC) $(FLAGS) $(BONUS_OBJ) -L$(P_LIB) -lft -o $(BONUS_NAME)

$(NAME): $(OBJ) $(P_LIB)libft.a
	$(CC) $(FLAGS) $(OBJ) -L$(P_LIB) -lft -o $@

$(P_LIB)libft.a: lib

$(P_MOBJ):
	mkdir -p $(P_MOBJ)

$(P_BOBJ):
	mkdir -p $(P_BOBJ)

$(P_MOBJ)%.o: $(P_SRC_MANDATORY)%.c $(HEADER) | $(P_MOBJ)
	$(CC) $(FLAGS) -c $< -I$(P_LIB) -I$(P_INC) -o $@

$(P_BOBJ)%.o: $(P_SRC_BONUS)%.c $(HEADER) | $(P_BOBJ)
	$(CC) $(FLAGS) -c $< -I$(P_LIB) -I$(P_INC) -o $@
