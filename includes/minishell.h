/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:55:11 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/19 17:42:34 by vhovhann         ###   ########.fr       */
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

typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*prev;
	char				*data;
	char				*key;
	int					flag;
}	t_env;

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
	WRITE_APPEND,
	WRITE_TRUNC,
	INPUT,
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
	char			*rpath;
	char			*lpath;
	int				err_code;
	int				subshell_code;
	int				*pipes[2];
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
void					free_2d(char **s);
void					free_n2d(char **s, int i);
int						check_digit(char *str);
char					*trim_zeroes(char *s);
unsigned long long int	ft_atll(char *str);
int						strlen_2d(char **str);
int						onlyspace(char *str);
int						parse_error(int fd, char *err, int mode);
char					*strjoin_mode(char *s1, char *s2, int mode);
int						error_code(int error_num);
int						env_lstsize(t_env *lst);
void					update_shlvl(t_env **env);
char					**env_2d(t_env *env);

/***********************************************/
/************* MINISHELL_BUILTINS **************/
/***********************************************/
void					minishell_env(char *str, t_env *env);
void					minishell_echo(char **arr);
void					minishell_cd(char **arr, t_env *my_env);
void					minishell_exit(char **arr, t_env *env);
void					minishell_pwd(char *str);
void					pwd_init(t_env *my_env);
void					handler_stp(int sig);
void					call_signals(void);
void					check_unset(char *str, t_env *my_env);
void					minishell_unset(char **arr, t_env *my_env);
void					minishell_export(char **arr, t_env *my_env);
void					ft_export(t_env *my_env);
int						ft_check(t_env *my_env, char *str);
void					ft_add(t_env *my_env, char *str);
t_env					*env_init(char **env, t_env *my_env);
t_env					*push_back(t_env **list, t_env *new);
t_env					*malloc_list(char *env);

void					lex(char *line, t_main *main);
int						ft_isspace(char *str, int start, int i);
int						is_delim(t_pars	*pars);
char					*type_is(t_type type);
int						check_valid(t_main *main);
int						check_types(t_type type);
int						check_redir(char *line, int i, int k);
int						lstsize(t_pars *lst);
char					*search_redir(char *str);
void					destroy_structure(t_pars *root);
void					destroy_main(t_main *main);

t_pars					*lstlast(t_pars *lst);
void					lstclear(t_pars **lst);
void					lstback(t_pars **pars, t_pars *new);
t_pars					*lstadd(char *string, t_type type, int prc, int flag);

int						handle_dquotes(t_pars **pars, char *line, \
							int i, int start);
int						handle_squotes(t_pars **pars, char *line, \
							int i, int start);

int						handle_xor(t_pars **pars, char *line, \
							int i, int start);
int						handle_xand(t_pars **pars, char *line, \
							int i, int start);
int						handle_pipe(t_pars **pars, char *line, \
							int i, int start);

int						handle_oprnth(t_pars **pars, char *line, \
							int i, int start);
int						handle_clprnth(t_pars **pars, char *line, \
							int i, int start);

int						handle_heredoc(t_pars **pars, char *line, \
							int i, int start);
void					handle_heredoc_input(char *string, t_pars **pars);

int						handle_append(t_pars **pars, char *line, \
							int i, int start);
int						handle_trunc(t_pars **pars, char *line, \
							int i, int start);
int						handle_infile(t_pars **pars, char *line, \
							int i, int start);

void					handle_space(t_pars **pars, char *line, \
							int i, int start);
void					handle_dollar(int exit_status, t_env *env);

char					**restore_cmd_line(t_pars *stack);
void					parsing(t_main *main);
void					delete_node(t_pars **opstack);
void					push(t_pars **a, t_pars **b);
void					shunting_yard(t_pars **tmp, t_pars **postfix, t_pars **opstack);
t_pars					*abstract_syntax_tree(t_main *main, t_pars **stack);
void					print_ast(t_pars *ast, int indent, int lrc);
t_pars					*most_prev(t_pars *stack);

int						check_astree(t_main *main, t_pars *stack, t_env *env);
int						cmds_execute(t_main *main, t_pars *pars, t_env *env, int status);
int						check_builtins(t_main *main, t_pars *pars, t_env *env);
int						check_xandxor(t_pars *stack);
int						call_cmds(t_main *main, t_pars *stack, t_env *env);
char					*check_cmd(char *cmd, char **path);
void					find_path(t_main *main, t_env *env);;
char					*fill_path_cmd(char *cmd, char **path);
int						exec_cmds(char *path_cmd, char **cmd_arr, char **env);
int						redir(t_main *main, t_pars *stack, t_env *env);
int 					heredoc(t_main *main, t_pars *stack, t_env *env);
int						input(t_main *main, t_pars *stack, t_env *env);
int 					exec_iocmd(t_main *main, t_pars *stack, t_env *env);

#endif
