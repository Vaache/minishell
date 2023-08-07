NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR 	= src
SUBDIRS 	= lexer get_next_line builtins utils
SRCDIRS 	:= $(addprefix $(SRC_DIR)/, $(SUBDIRS))
SRCS		:= $(notdir $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))) $(notdir $(SRC_DIR)/main.c)

OBJ_DIR		= obj

OBJ 		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBS		= libft Fdprintf
LIBFT_DIR	= ./libs/libft
PRINTF_DIR	= ./libs/Fdprintf
INCLUDES	= /includes

HEADER		= $(wildcard includes/*.h) \
				$(wildcard $(LIBFT_DIR)libft.h) \
				$(wildcard $(PRINTF_DIR)/ft_printf.h)

SANITIZER	= -g3 -fsanitize=address
INCLUDE		= -Iincludes -I./readline_update/include -I$(PRINTF_DIR)/$(INCLUDES) -I$(LIBFT_DIR)/$(INCLUDES)
LINKERS		= -L$(LIBFT_DIR) -lft -L./readline_update/lib -lreadline -L$(PRINTF_DIR) -lftprintf
MK			= mkdir -p
PREFIX		= $(shell find ${HOME} -name readline_update 2>/dev/null)


TEXT		= "\033[6;1m"
BLUE		= "\033[38;2;158;204;245m"
PURPLE		= "\033[38;2;0;138;240m"
RESET		= "\033[0m"

# test :
# 	@echo $(HEADER)

all: $(LIBS) $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile
	@echo $(BLUE) "$(CC) $(CFLAGS) $(SANITIZER) $(INCLUDE) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c $(HEADER) Makefile
	@echo $(BLUE) "$(CC) $(CFLAGS) $(SANITIZER) $(INCLUDE) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@$(MK) $(OBJ_DIR)

libft :
	@make -C $(LIBFT_DIR)

Fdprintf :
	@make -C $(PRINTF_DIR)

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

$(NAME): $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(LINKERS) $(LIBFT) -o $(NAME) $(OBJ)
	@echo $(PURPLE) $(TEXT) COPILED$(RESET)
	
clean:
	@rm -f $(OBJ)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)
	
fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all $(LIBS) clean fclean re