/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_astree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:48:15 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/08 15:23:25 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_astree(t_main *main, t_tok *stack, t_env **env);
void	check_astree_1(t_main *main, t_tok **stack, t_env **env);
void	check_astree_2(t_main *main, t_tok **stack, t_env **env);
int		ast_left_branch(t_main *main, t_tok **stack, t_env **env);
int		ast_right_branch(t_main *main, t_tok **stack, t_env **env);

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
	return (stack->err_code);
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
		(*stack)->err_code = ast_left_branch(main, &(*stack), env);
	}
	if ((*stack)->right != NULL && andxor((*stack)) && \
		!((*stack)->right->flag & _REDIR_) && !((*stack)->right->flag & _PIPE_))
	{
		check_lasts(main, (*stack), 1);
		(*stack)->err_code = ast_right_branch(main, stack, env);
	}
	handle_dollar((*stack)->err_code, env);
}

int	ast_left_branch(t_main *main, t_tok **stack, t_env **env)
{
	pid_t	pid;
	int		status;

	status = 0;
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
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		(*stack)->err_code = status / 256;
	}
	else
		(*stack)->err_code = check_astree(main, (*stack)->left, env);
	return ((*stack)->err_code);
}

int	ast_right_branch(t_main *main, t_tok **stack, t_env **env)
{
	pid_t	pid;
	int		status;

	status = 0;
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
		if (wait(&status) < 0)
		{
			perror("minishell");
			return (1);
		}
		(*stack)->err_code = status / 256;
	}
	else
		(*stack)->err_code = check_astree(main, (*stack)->right, env);
	return ((*stack)->err_code);
}
