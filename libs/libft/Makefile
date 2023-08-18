NAME		= libft.a
HEADER		= libft.h
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
SRCS		= $(wildcard $(SRC_DIR)/*.c)

OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

HEADER	= $(wildcard ./includes/*.h)
INCLUDE	= -Iincludes

GREEN		= "\033[38;2;49;247;196m"
# PURPLE		= "\033[38;2;158;204;245m"
RESET		= "\033[0m"

.PHONY : all clean fclear re

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR) : 
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) Makefile
	@echo $(GREEN) "$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	

$(NAME) : $(OBJ) $(HEADER)
	@ar rcs $(NAME) $(OBJ)

clean :
	@rm -f $(OBJ)

fclean :
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)

re : fclean all

