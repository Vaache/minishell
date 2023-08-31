/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:55:11 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 16:03:38 by vhovhann         ###   ########.fr       */
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

# define _CD_		"cd"
# define _PWD_		"pwd"
# define _ENV_		"env"
# define _EXIT_		"exit"
# define _ECHO_		"echo"
# define _UNSET_	"unset"
# define _EXPORT_	"export"
# define _PIPE_		32
# define _REDIR_	8

typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*prev;
	char				*data;
	char				*key;
	char				*pwd;
	int					flag;
}	t_env;

typedef struct s_wcard
{
	struct s_wcard		*next;
	struct s_wcard		*prev;
	char				*file;
}	t_wcard;

typedef enum e_token_type
{
	WORD,
	DQUOTE,
	SQUOTE,
	SUBSH_OPEN,
	SUBSH_CLOSE,
	XOR,
	XAND,
	HEREDOC,
	PIPE,
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
	int				last_red;
	int				last_hdoc;
	int				last_input;
	int				pipes[2];
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
	int			redir;
	int			hdoc;
	int			input;
	int			flag;
	char		**path;
	int			stdin_backup;
	t_pars		*pars;
	t_pars		*lex;
	t_pars		*temp;
}				t_main;
/********************************************/
/************* MINISHELL_UTILS **************/
/********************************************/
void					print_header(void);
int						free_2d(char **s);
void					free_n2d(char **s, int i);
int						free_of_n(char *str, char **arr1, char **arr2, int i);
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
char					**env_2d(t_env **env);
void					builtins_error(char	*str, char *err);
int						_close3_(int fd1, int fd2, int fd3);
int						_close2_(int fd1, int fd2);
int						_close_(int	fd);
int						close_pipes(int fd[2]);
int						quote_count(char *limiter);

/***********************************************/
/************* MINISHELL_BUILTINS **************/
/***********************************************/
void					minishell_env(t_env **env);
void					minishell_echo(char **arr);
void					minishell_cd(char **arr, t_env **my_env);
void					minishell_exit(char **arr, t_env **env);
void					minishell_pwd(char *str, t_env **env);
int						minishell_unset(char **arr, t_env **my_env);
void					minishell_export(char **arr, t_env **my_env);
int						check_unset(char *str);
void					pwd_init(t_env **my_env);
void					handler_stp(int sig);
void					call_signals(void);
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
char					*handle_heredoc_input(char *string);

int						handle_append(t_pars **pars, char *line, \
							int i, int start);
int						handle_trunc(t_pars **pars, char *line, \
							int i, int start);
int						handle_infile(t_pars **pars, char *line, \
							int i, int start);

void					handle_space(t_pars **pars, char *line, \
							int i, int start);
void					handle_dollar(int exit_status, t_env **env);

char					**restore_cmd_line(t_pars *stack, int i);
void					parsing(t_main *main);
void					delete_node(t_pars **opstack);
void					push(t_pars **a, t_pars **b);
void					shunting_yard(t_pars **tmp, t_pars **postfix, \
														t_pars **opstack);
t_pars					*abstract_syntax_tree(t_main *main, t_pars **stack);
t_pars					*most_prev(t_pars *stack);

int						check_astree(t_main *main, t_pars *stack, t_env **env);
int						cmds_execute(t_main *main, t_pars *pars, t_env **env, \
															int status);
void					print_ast(t_pars *ast, int indent, int lrc);
int						check_builtins(t_main *main, t_pars *pars, t_env **env);
t_type					ttoa(char *token);
int						find_limiter_end(char *line, int i, int start);
char					*rem_quotes_lim(char *limiter);
char					*token_is(t_type token);
int						andxor(t_pars *stack);
int						call_cmds(t_main *main, t_pars *stack, t_env **env);
char					*check_cmd(char *cmd, char **path);
void					find_path(t_main *main, t_env **env);;
char					*fill_path_cmd(char *cmd, char **path);
int						exec_cmds(char *path_cmd, char **cmd_arr, char **env, int stdin_backup);
int						redir(t_main *main, t_pars *stack, t_env **env);
int						heredoc(t_main *main, t_pars *stack, t_env **env);
int						input(t_main *main, t_pars *stack, t_env **env);
int						exec_iocmd(t_main *main, t_pars *stack, t_env **env);
int						pipe_prepair(t_main *main, t_pars *pars, t_env **env);

void					get_file(char *path, t_wcard **wcard);
t_wcard					*lstadd_wcard(char *string);
void					lstback_wcard(t_wcard **pars, t_wcard *new);
void					lstclear_wcard(t_wcard **lst);
int						lstsize_wcard(t_wcard *lst);

#endif
