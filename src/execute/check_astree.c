/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_astree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:48:15 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/07 20:31:14 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_astree(t_main *main, t_tok *stack, t_env **env);
void	check_astree_1(t_main *main, t_tok **stack, t_env **env);
void	check_astree_2(t_main *main, t_tok **stack, t_env **env);
int		ast_child(t_main *main, t_tok **stack, t_env **env);
int		ast_child_orxand(t_main *main, t_tok **stack, t_env **env);

int	check_astree(t_main *main, t_tok *stack, t_env **env)
{
	int		status;

	status = 0;
	if (!stack)
	{
		g_exit_status_ = 258;
		return (g_exit_status_);
	}
	if (stack->left == NULL && stack->right == NULL)
	{
		g_exit_status_ = cmds_execute(main, stack, env, status);
		handle_dollar(g_exit_status_, env);
		return (g_exit_status_);
	}
	if (stack->left && stack->right && (check_types(stack->type) == 2))
		check_astree_1(main, &stack, env);
	else if (stack->left && stack->right && stack->type == PIPE)
			stack->err_code = pipe_prepair(main, stack, env);
	else
		check_astree_2(main, &stack, env);
	return (0);
}

void	check_astree_1(t_main *main, t_tok **stack, t_env **env)
{
	check_lasts(main, *stack, 0);
	if ((*stack)->left->left)
		check_astree(main, (*stack)->left, env);
	if (g_exit_status_ != EXIT_FAILURE)
		g_exit_status_ = exec_iocmd(main, (*stack), env);
	if ((*stack)->hdoc_fname)
		unlink((*stack)->hdoc_fname);
}

void	check_astree_2(t_main *main, t_tok **stack, t_env **env)
{
	if ((*stack)->left != NULL && !((*stack)->left->flag & _REDIR_) \
		&& !((*stack)->right->flag & _PIPE_))
	{
		check_lasts(main, (*stack), 1);
		ast_child(main, &(*stack), env);
		handle_dollar(g_exit_status_, env);
	}
	if ((*stack)->right != NULL && andxor((*stack)) && \
		!((*stack)->right->flag & _REDIR_) && !((*stack)->right->flag & _PIPE_))
	{
		check_lasts(main, (*stack), 1);
		ast_child_orxand(main, stack, env);
		handle_dollar(g_exit_status_, env);
	}
}

int	ast_child(t_main *main, t_tok **stack, t_env **env)
{
	pid_t	pid;
	int		chidle_exit;

	chidle_exit = 0;
	if ((*stack)->left->subshell_code && check_types((*stack)->left->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			(*stack)->err_code = check_astree(main, (*stack)->left, env);
			exit((*stack)->err_code);
		}
		else
		{
			waitpid(pid, &chidle_exit, 0);
			g_exit_status_ = chidle_exit % 255;
			handle_dollar(g_exit_status_, env);
		}
	}
	else
		(*stack)->err_code = check_astree(main, (*stack)->left, env);
	return (chidle_exit / 255);
}

int	ast_child_orxand(t_main *main, t_tok **stack, t_env **env)
{
	pid_t	pid;
	int		chidle_exit;

	chidle_exit = 0;
	if ((*stack)->right->subshell_code && \
		check_types((*stack)->right->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			(*stack)->err_code = check_astree(main, (*stack)->right, env);
			exit ((*stack)->err_code);
		}
		else
		{
			waitpid(pid, &chidle_exit, 0);
			g_exit_status_ = chidle_exit % 255;
			handle_dollar(g_exit_status_, env);
		}
	}
	else
		(*stack)->err_code = check_astree(main, (*stack)->right, env);
	return (chidle_exit / 255);
}
