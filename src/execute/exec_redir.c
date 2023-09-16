/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:41:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/16 19:14:46 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_main *main, t_tok *stack, t_env **env);
int	input(t_main *main, t_tok *stack, t_env **env);
int	heredoc(t_main *main, t_tok *stack, t_env **env);
int	exec_iocmd(t_main *main, t_tok *stack, t_env **env);

int	redir(t_main *main, t_tok *stack, t_env **env)
{
	int		fd;
	t_tok	*tmp;

	fd = open_out(stack);
	if (fd < 0)
		return (1);
	tmp = stack;
	while (tmp->left->type != WORD && check_types(tmp->left->type) != 1)
		tmp = tmp->left;
	tmp->left->stdout_backup = main->stdout_backup;
	tmp->left->_stdout_ = fd;
	if (check_types(stack->type) == 2 && stack->sub)
		stack->last_red = 1;
	if (stack->last_red != 1 || (check_types(stack->left->type) == 2 && \
			stack->left->sub))
		return (0);
	if (ft_strcmp(tmp->left->cmd, "(NULL)") && !(tmp->flag & (1 << 7)))
		stack->err_code = check_astree(main, tmp->left, *env);
	return (stack->err_code);
}

int	heredoc(t_main *main, t_tok *stack, t_env **env)
{
	t_tok	*tmp;
	int		fd;

	fd = open(stack->hdoc_fname, O_RDWR, 0655);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	tmp->left->stdin_backup = main->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (check_types(stack->type) == 2 && stack->sub)
		stack->last_hdoc = 1;
	if (stack->last_hdoc != 1 || tmp->left->type == PIPE || \
			(check_types(stack->left->type) == 2 && stack->left->sub))
		return (0 + unlink(stack->hdoc_fname));
	if (ft_strcmp(stack->right->cmd, "(NULL)"))
		stack->err_code = execute_second_arg(main, stack, *env);
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
		stack->err_code |= cmds_execute(main, tmp->left, env, 0);
	return (stack->err_code);
}

int	input(t_main *main, t_tok *stack, t_env **env)
{
	static int	i = 0;
	int			fd;
	t_tok		*tmp;

	if (i == 1)
		return (1);
	fd = open_input(stack);
	if (fd < 0)
	{
		i = 1;
		return (1);
	}
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	if (check_types(stack->type) == 2 && stack->sub)
		stack->last_input = 1;
	tmp->left->stdin_backup = main->stdin_backup;
	tmp->left->_stdin_ = fd;
	if (stack->last_input != 1 || (check_types(stack->left->type) == 2 && \
															stack->left->sub))
		return (0);
	stack->err_code |= check_astree(main, tmp->left, *env);
	i = 0;
	return (stack->err_code);
}

int	exec_iocmd(t_main *main, t_tok *stack, t_env **env)
{
	check_lasts(main, stack, 0);
	if (stack->left->left && check_types(stack->left->type) == 2)
		stack->err_code = check_astree(main, stack->left, *env);
	if (main->exit_status == EXIT_SUCCESS)
	{
		if (stack && stack->type == HEREDOC)
			return (heredoc(main, stack, env));
		else if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
			return (redir(main, stack, env));
		else if (stack->type == INPUT)
			return (input(main, stack, env));
	}
	if (stack->hdoc_fname)
		unlink(stack->hdoc_fname);
	return (stack->err_code);
}
