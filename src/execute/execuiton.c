/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuiton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:11:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 19:24:08 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_astree(t_main *main, t_pars *stack, t_env *env);

int	check_astree(t_main *main, t_pars *stack, t_env *env)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (!stack)
	{
		main->exit_status = 258;
		return (main->exit_status);
	}
	if (stack->left == NULL && stack->right == NULL)
	{
		main->exit_status = cmds_execute(main, stack, env, status);
		return (1);
	}
	if (stack->left != NULL && !(stack->left->flag & (1 << 3)))
	{
		if (stack->left->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				stack->err_code = check_astree(main, stack->left, env);
			}
			else
			{
				if (wait(&status) < 0)
				{
					perror("wait");
						return (1);
				}
				return (status);
			}
		}
		else
			stack->err_code = check_astree(main, stack->left, env);
	}
	if (stack->right != NULL && !(stack->right->flag & (1 << 3)))
	{
		if (stack->right->subshell_code)
		{
			pid = fork();
			if (pid == -1)
				return (127);
			else if (pid == 0)
			{
				stack->err_code = check_astree(main, stack->right, env);
			}
			else
				wait(NULL);
			return (1);
		}
		else
			stack->err_code = check_astree(main, stack->right, env);
	}
	return (0);
}