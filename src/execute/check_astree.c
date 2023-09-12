/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_astree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:48:15 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 21:07:52 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_astree(t_main *main, t_tok *root, t_env *env);
int		ast_left_branch(t_main *main, t_tok **stack, t_env **env, int status);
int		ast_right_branch(t_main *main, t_tok **stack, t_env **env, int status);

int	check_astree(t_main *main, t_tok *root, t_env *env)
{
	int		status;

	status = 0;
	if (!root)
	{
		root->err_code = 258;
		return (root->err_code);
	}
	if (root->left == NULL && root->right == NULL)
	{
		root->err_code = cmds_execute(main, root, &env, 0);
		return (root->err_code);
	}
	if (root->left && root->right && check_types(root->type) == 2)
		root->err_code = exec_iocmd(main, root, &env);
	else if (root->left && root->right && root->type == PIPE)
		root->err_code = pipe_prepair(main, root, &env);
	if (root->left != NULL && !(root->left->flag & _REDIR_) && \
		!(root->left->flag & _PIPE_))
		root->err_code = ast_left_branch(main, &root, &env, status);
	if (root->right != NULL && andxor(root) && \
		!(root->right->flag & (_REDIR_)) && !(root->right->flag & _PIPE_))
		root->err_code = ast_right_branch(main, &root, &env, status);
	handle_dollar(root->err_code, &env);
	return (root->err_code);
}

int	ast_left_branch(t_main *main, t_tok **stack, t_env **env, int status)
{
	pid_t	pid;

	if (check_lasts(main, *stack, 1) && (*stack)->left->subshell_code && \
									check_types((*stack)->left->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			(*stack)->err_code = check_astree(main, (*stack)->left, *env);
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
		(*stack)->err_code = check_astree(main, (*stack)->left, *env);
	return ((*stack)->err_code);
}

int	ast_right_branch(t_main *main, t_tok **stack, t_env **env, int status)
{
	pid_t	pid;

	if (check_lasts(main, *stack, 1) && (*stack)->right->subshell_code && \
		check_types((*stack)->right->type) == 1)
	{
		pid = fork();
		if (pid == -1)
			return (127);
		else if (pid == 0)
		{
			(*stack)->err_code = check_astree(main, (*stack)->right, *env);
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
		(*stack)->err_code = check_astree(main, (*stack)->right, *env);
	return ((*stack)->err_code);
}
