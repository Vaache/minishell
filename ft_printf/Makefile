NAME		= libftprintf.a
HEADER		= ft_printf.h
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(HEADER)
SRC			= $(wildcard *.c)

OBJ			= $(SRC:.c=.o)

BLUE		= "\033[38;2;158;204;245m"
# PURPLE		= "\033[38;2;158;204;245m"
RESET		= "\033[0m"

.PHONY : all clean fclear  re

all : $(NAME)

%.o : %.c $(HEADER) Makefile
	@echo $(BLUE) "$(CC) $(CFLAGS) -c $< -o $@" $(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@
	

$(NAME) : $(OBJ) $(HEADER)
	@ar rcs $(NAME) $?

clean :
	@rm -f $(OBJ)

fclean :
	@rm -f $(OBJ)
	@rm -rf $(NAME)

re : fclean all

