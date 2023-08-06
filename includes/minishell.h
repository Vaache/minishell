/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:55:11 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/06 15:50:36 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "get_next_line_bonus.h"
# include "libft.h"
# include "ft_printf.h"

# define PWD	"pwd"
# define ENV 	"env"
# define EXIT	"exit"
# define UNSET	"unset"
# define EXPORT	"export"

typedef struct s_env_list
{
	struct s_env_list	*next;
	struct s_env_list	*prev;
	char				*data;
	char				*key;
	char				*line;
	int					flag;
}	t_env_list;

typedef enum e_token_type
{
	WORD,
	DQUOTE,
	SQUOTE,
	SUBSH_OPEN,
	SUBSH_CLOSE,
	XOR,
	XAND,
	PIPE,
	HEREDOC,
	HEREDOC_ARG,
	WRITE_APPEND,
	WRITE_TRUNC,
	INPUT,
	FILEIN,
	FILEOUT,
	END,
}	t_type;


//	@brief
//	@tparam char		*cmd
//	@tparam	char		*rpath
//	@tparam	char		*lpath
//	@tparam	t_type		type
//	@tparam int			prc
//	@tparam	int			flag
//	@tparam	int			err_code
//	@tparam	int			(*pipes)[2]
//	@tparam	s_parser	*next
//	@tparam	s_parser	*prev
//	@tparam	s_parser	*left
//	@tparam	s_parser	*right
typedef struct s_pars
{
	char			*cmd;
	t_type			type;
	int				prc;
	int				flag;
	int				err_code;
	int				*pipes;
	struct s_pars	*next;
	struct s_pars	*prev;
	struct s_pars	*left;
	struct s_pars	*right;
}					t_pars;

//	@brief
//	@tparam int			exit_status
//	@tparam	char		**path
//	@tparam	t_parser	*pars
//	@tparam	t_parser	*lex
//	@tparam	t_parser	*temp
typedef struct s_main
{
	int			exit_status;
	char		**path;
	t_pars		*pars;
	t_pars		*lex;
	t_pars		*temp;
}				t_main;

/********************************************/
/************* MINISHELL_UTILS **************/
/********************************************/
void					print_header(void);
void					free_2dd(char **s);
void					free_2d(char **s, int i);
int						check_digit(char *str);
char					*trim_zeroes(char *s);
unsigned long long int	ft_atll(char *str);
int						strlen_2d(char **str);
int						onlyspace(char *str);

void					call_signals(void);
void					check_unset(char *arr, t_env_list *my_env);

void					builtins(char *str, t_env_list *my_env);
void					builtins_2(char *str, t_env_list *my_env);
void					builtins_3(char *str);
void					builtins_4(char *str, t_env_list *my_env);
void					ft_export(t_env_list *my_env);
int						ft_check(t_env_list *my_env, char *str);
void					ft_add(t_env_list *my_env, char *str);

t_env_list				*env_init(char **env, t_env_list *my_env);
t_env_list				*push_back(t_env_list **list, t_env_list *new);
t_env_list				*malloc_list(char *env);
void					pwd_init(t_env_list *my_env);
void					lex(char *line, t_main *main);
int						ft_isspace(char *str, int i, int j);
int						is_delim(t_pars	*pars);

t_pars					*lstlast(t_pars *lst);
void					lstclear(t_pars **lst);
void					lstback(t_pars **pars, t_pars *new);
t_pars					*lstadd(char *string, t_type type, int prc, int flag);

int						handel_dquotes(t_pars **pars, char *line, int i, int start);
int						handel_squotes(t_pars **pars, char *line, int i, int start);


#endif
