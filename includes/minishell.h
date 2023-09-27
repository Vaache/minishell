/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:55:11 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/27 16:57:57 by vhovhann         ###   ########.fr       */
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
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"
# include "ft_printf.h"
# include <sys/ioctl.h>

# define _CD_		"cd"
# define _PWD_		"pwd"
# define _ENV_		"env"
# define _EXIT_		"exit"
# define _ECHO_		"echo"
# define _UNSET_	"unset"
# define _EXPORT_	"export"
# define _PIPE_		32
# define _REDIR_	8

typedef struct s_hd
{
	char	**matrix;
	int		i;
}	t_hd;

typedef struct s_env
{
	struct s_env		*next;
	struct s_env		*prev;
	char				*data;
	char				*key;
	char				*pwd;
	int					flag;
}	t_env;

typedef struct s_exp
{
	int		i;
	int		l;
	char	*str;
	char	*s;
}	t_exp;

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
//	@tparam	s_toker	*next
//	@tparam	s_toker	*prev
//	@tparam	s_toker	*left
//	@tparam	s_toker	*right
typedef struct s_tok
{
	char			*cmd;
	char			*exit_tmp;
	char			*hdoc_fname;
	t_type			type;
	int				prc;
	int				flag;
	int				err_code;
	int				sub;
	int				last_red;
	int				last_hdoc;
	int				last_input;
	int				_stdin_;
	int				_stdout_;
	int				stdin_backup;
	int				stdout_backup;
	int				fd;
	int				pipes[2];
	struct s_tok	*next;
	struct s_tok	*prev;
	struct s_tok	*left;
	struct s_tok	*right;
}					t_tok;

//	@brief
//	@tparam int			exit_status
//	@tparam	char		**path
//	@tparam	t_toker	*pars
//	@tparam	t_toker	*lex
//	@tparam	t_toker	*temp
typedef struct s_main
{
	int			exit_status;
	int			redir;
	int			hdoc;
	int			input;
	int			flag;
	char		**path;
	int			last_hdoc;
	int			last_redir;
	int			last_input;
	int			stdin_backup;
	int			stdout_backup;
	int			builtins_err;
	t_tok		*pars;
	t_tok		*lex;
	t_tok		*temp;
	t_hd		*hd;
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
char					**env_2d(t_env **env);
void					builtins_error(char	*str, char *err);
int						_close3_(int fd1, int fd2, int fd3);
int						_close2_(int fd1, int fd2);
int						_close_(int fd);
int						close_pipes(int fd[2]);
int						quote_count(char *limiter);
void					save_backup(t_main **main);
void					main_init(t_main *main);
void					init_hd(t_hd **hd);
int						check_subsh(t_tok *stack);
int						check_for_lexer(char *line, int i);

/***********************************************/
/************* MINISHELL_BUILTINS **************/
/***********************************************/
void					minishell_env(t_env **env);
void					minishell_echo(char **arr);
void					minishell_cd(char **arr, t_env **my_env);
void					minishell_pwd(char *str, t_env **env);
int						minishell_unset(char **arr, t_env **my_env);
int						minishell_exit(t_tok *stack, char **arr, t_env **env, \
																	char *s);
void					minishell_export(char **arr, t_env **my_env);
int						call_expand(t_tok *stack, t_env *env);
char					*expand(char *str, t_env **env, t_exp *exp);
int						check_unset(char *str);
void					pwd_init(t_env **my_env);
void					run_signals(int sig);
void					restore_prompt(int sig);
void					ctrl_c(int sig);
void					back_slash(int sig);
void					ft_export(t_env *my_env);
int						ft_check(t_env *my_env, char *str);
void					ft_add(t_env *my_env, char *str);
t_env					*env_init(char **env, t_env *my_env);
t_env					*push_back(t_env **list, t_env *new);
t_env					*malloc_list(char *env);

void					lex(char **line, t_main *main, t_env *env);
int						ft_isspace(char *str, int start, int i);
int						is_delim(t_tok	*pars);
char					*type_is(t_type type);
int						check_valid(t_main *main, t_env *env, int *sb, int flag);
int						check_types(t_type type);
int						lstsize(t_tok *lst);
void					destroy_structure(t_tok *root);
void					destroy_main(t_main *main);
void					destroy_exp(t_exp *exp);

t_tok					*lstlast(t_tok *lst);
void					lstclear(t_tok **lst);
void					lstback(t_tok **pars, t_tok *new);
t_tok					*lstadd(char *string, t_type type, int prc, int flag);

int						handle_quotes(t_tok **res, char **line, int *i, \
																int count);
int						handle_dquotes(t_tok **pars, char **line, int *i, \
																int start);
int						handle_squotes(t_tok **pars, char **line, int *i, \
																int start);

int						handle_xor(t_tok **pars, char *line, \
							int i, int start);
int						handle_xand(t_tok **pars, char *line, \
							int i, int start);
int						handle_pipe(t_tok **pars, char *line, \
							int i, int start);

int						handle_oprnth(t_tok **pars, char *line, \
							int i, int start);
int						handle_clprnth(t_tok **pars, char *line, \
							int i, int start);

int						handle_heredoc(t_tok **pars, char *line, \
							int i, int start);
int						heredoc_input(t_main *main, t_env *env);
int						read_heredoc_input(t_main *main, t_tok *tok, \
							char *line, t_env *env);

int						handle_append(t_tok **pars, char *line, \
							int i, int start);
int						handle_trunc(t_tok **pars, char *line, \
							int i, int start);
int						handle_infile(t_tok **pars, char *line, \
							int i, int start);

void					handle_space(t_tok **pars, char *line, \
							int i, int start);
void					handle_dollar(int exit_status, t_env **env);
void					find_limiter(t_main *main, t_tok *stack);
void					push_redir(t_tok *to, t_tok *from);
void					pop_redir(t_tok *tok);

void					delete_node(t_tok **opstack);
void					push(t_tok **a, t_tok **b);
void					shunting_yard(t_tok **tmp, t_tok **postfix, \
														t_tok **opstack);
t_tok					*abstract_syntax_tree(t_main *main, t_tok **stack);
t_tok					*most_prev(t_tok *stack);

t_tok					*ast_branch(t_tok *tok);
int						check_astree(t_main *main, t_tok *root, t_env *env);
int						cmds_execute(t_main *main, t_tok *pars, t_env **env, \
															int status);

char					**restore_cmd_line(t_tok *stack, int i);
void					parsing(t_main *main);
int						check_lasts(t_main *main, t_tok *stack, int mode);
t_type					ttoa(char *token);
char					*token_is(t_type token);
int						andxor(t_tok *stack);
int						call_cmds(t_main *main, t_tok *stack, t_env **env);
char					*check_cmd(t_main *main, t_tok *stack, char *cmd, \
															char **path);
int						execute_second_arg(t_main *main, t_tok *stack, \
																t_env *env);
t_tok					*find_second_arg(t_tok *stack);
void					find_path(t_main *main, t_env **env);;
char					*fill_path_cmd(char *cmd, char **path);
int						exec_cmds(char *path_cmd, char **cmd_arr, char **env, \
									t_tok *stack);
int						redir(t_main *main, t_tok *stack, t_env **env);
int						heredoc(t_main *main, t_tok *stack, t_env **env);
int						input(t_main *main, t_tok *stack, t_env **env);
int						exec_iocmd(t_main *main, t_tok *stack, t_env **env);
int						pipe_prepair(t_main *main, t_tok *pars, t_env **env);
int						io_dup2(int _stdin_, int _stdout_);
int						io_backup_dup2(int _stdin_backup_, int _stdout_backup_);
void					config_left_dups(t_tok *stack);
void					config_right_dups(t_tok *stack);
int						open_out(t_tok *stack);
int						open_input(t_tok *stack);

void					get_file(char *path, t_wcard **wcard);
t_wcard					*lstadd_wcard(char *string);
void					lstback_wcard(t_wcard **pars, t_wcard *new);
void					lstclear_wcard(t_wcard **lst);
int						lstsize_wcard(t_wcard *lst);

int						g_exit_status_;

#endif
