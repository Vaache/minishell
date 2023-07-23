#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "get_next_line_bonus.h"
#include "libft.h"

# define PWD	"pwd"
# define ENV 	"env"
# define UNSET	"unset"

typedef struct s_env_list
{
	struct s_env_list	*next;
	struct s_env_list	*prev;
	char				*data;
	char				*key;
	char				*line;
	int					*flag;
}	t_env_list;

void			print_header(void);
void			call_signals();
void			check_unset(char *arr, t_env_list *my_env);
void			builtins(char *str, t_env_list *my_env);
t_env_list		*env_init(char **env, t_env_list *my_env);
t_env_list		*push_back(t_env_list **list, t_env_list *new);
t_env_list		*malloc_list(char *env);
void			unset_fnc(t_env_list *list, char *str);

#endif