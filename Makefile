NAME	= minishell

SRC_DIR = src

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR	= obj

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

CC			= cc
HEADER		= $(wildcard includes/*.h) $(wildcard libft/libft.h) $(wildcard ft_printf/ft_printf.h)
INCLUDE		= -Iincludes -I./readline_update/include -Ilibft -Ift_printf
LINKERS		= -L./libft -lft -L./readline_update/lib -lreadline -L./ft_printf -lftprintf
CFLAGS		= -Wall -Wextra -Werror $(INCLUDE) -g3 -fsanitize=address
MK			= mkdir -p
PREFIX		= $(shell find ${HOME} -name readline_update 2>/dev/null)
TEXT		= "\033[6;1m"
BLUE		= "\033[38;2;158;204;245m"
PURPLE		= "\033[38;2;0;138;240m"
RESET		= "\033[0m"

all: ft_printf libft $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	@echo $(BLUE) "$(CC) $(CFLAGS) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

libft :
	@make -C libft
	
ft_printf :
	@make -C ft_printf

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $() $(LINKERS) $(LIBFT) -o $(NAME) $(OBJ)
	@echo $(PURPLE) $(TEXT) COPILED$(RESET)
	
clean:
	@rm -f $(OBJ)
	@make fclean -C libft
	@make clean -C ft_printf
	
fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C libft
	@make fclean -C ft_printf

re: fclean all

.PHONY: all libft ft_printf clean fclean re