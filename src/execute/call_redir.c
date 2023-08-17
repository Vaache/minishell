/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:41:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/17 17:31:00 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_redir(t_main *main, t_pars *stack, t_env *env)
{
	int	fd;
	int	stdout_beckup;
	int	exit_status;

	fd = 0;
	stdout_beckup = 0;
	exit_status = 0;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_APPEND, 00755);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_WRONLY | O_CREAT | O_TRUNC, 00755);
	if (fd == -1)
	{
		perror("Minishell");
		return (1);
	}
	stdout_beckup = dup(STDOUT_FILENO);
	if (stdout_beckup == -1)
	{
		perror("Minishell");
		close(fd);
		return (1);
	}
	if (fd != 0 && dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Minishell");
		close(fd);
		return (1);
	}
	if (ft_strcmp(stack->left->cmd, "(NULL)"))
		exit_status = cmds_execute(main, stack->left, env, 0);
	if (fd != 0 && dup2(stdout_beckup, STDOUT_FILENO) == -1)
	{
		perror("Minishell");
		close(fd);
		return (1);
	}
	close(fd);
	close(stdout_beckup);
	return (exit_status);
}