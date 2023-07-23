NAME	= minishell

SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR	= obj

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC			= cc
HEADER		= $(wildcard includes/*.h) $(wildcard libft/libft.h)
INCLUDE		= -Iincludes -I./readline_update/include -Ilibft
LINKERS		= -L./libft -lft -L./readline_update/lib -lreadline
CFLAGS		= -Wall -Wextra -Werror $(INCLUDE) #-g3 -fsanitize=address
MK			= mkdir -p
PREFIX		= $(shell find ${HOME} -name readline_update 2>/dev/null)
TEXT		= "\033[6;1m"
BLUE		= "\033[38;2;158;204;245m"
PURPLE		= "\033[38;2;0;138;240m"
RESET		= "\033[0m"

# test :
# 	@echo $(INCLUDE)

all: libft $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	@echo $(BLUE) "$(CC) $(CFLAGS) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

libft :
	@make -C libft

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $() $(LINKERS) $(LIBFT) -o $(NAME) $(OBJ)
	@echo $(PURPLE) $(TEXT) COPILED$(RESET)
clean:
	@rm -f $(OBJ)
	@make clean -C libft
	
fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft

re: fclean all

.PHONY: all libft clean fclean re