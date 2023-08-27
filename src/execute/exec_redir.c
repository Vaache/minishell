/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:41:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/27 14:57:26 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_main *main, t_pars *stack, t_env *env);
int	heredoc(t_main *main, t_pars *stack, t_env *env);
int	input(t_main *main, t_pars *stack, t_env *env);
int	exec_iocmd(t_main *main, t_pars *stack, t_env *env);

int	redir(t_main *main, t_pars *stack, t_env *env)
{
	int	fd;
	int	stdout_beckup;
	int	exit_status;

	fd = 0;
	stdout_beckup = 0;
	exit_status = 0;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_APPEND, 0655);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_TRUNC, 0655);
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
	while (stack->left->type != WORD)
		stack = stack->left;
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

int	heredoc(t_main *main, t_pars *stack, t_env *env)
{
	int		stdin_backup;
	char	*res;
	int		fd;
	t_pars	*tmp;

	if (stack->left->type == HEREDOC)
		res = handle_heredoc_input(stack->left->right->cmd);
	res = handle_heredoc_input(stack->right->cmd);
	if (!res)
		return (1);
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup < 0)
	{
		perror("minshell");
		return (EXIT_FAILURE);
	}
	write(fd, res, ft_strlen(res));
	close(fd);
	free(res);
	fd = open(".heredoc", O_RDWR, 0655);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell");
		unlink(".heredoc");
		return (EXIT_FAILURE + _close2_(fd, stdin_backup));
	}
	close(fd);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
		main->exit_status = check_astree(main, tmp->left, env);
	if (dup2(stdin_backup, STDIN_FILENO) < 0)
	{
		perror("minishell");
		unlink(".heredoc");
		return (EXIT_FAILURE + _close2_(fd, stdin_backup));
	}
	close(stdin_backup);
	return (0);
}

int	input(t_main *main, t_pars *stack, t_env *env)
{
	int		file_fd;
	int		backup;

	backup = dup(STDIN_FILENO);
	file_fd = open(stack->right->cmd, O_RDONLY);
	if (file_fd < 0)
	{
		perror("minishell");
		return(EXIT_FAILURE + _close_(backup));
	}
	if (dup2(file_fd, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE + _close2_ (file_fd, backup));
	}
	while (stack->left->type != WORD)
		stack = stack->left;
	main->exit_status = cmds_execute(main, stack->left, env, 0);
	if (dup2(backup, STDIN_FILENO) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	return (0 + _close2_(backup, file_fd));
}

int	exec_iocmd(t_main *main, t_pars *stack, t_env *env)
{
	if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
		return (redir(main, stack, env));
	// else if (stack && stack->type == HEREDOC)
	// 	return (heredoc(main, stack, env));
	else if (stack->type == INPUT)
		return (input(main, stack, env));
	return (1);
}
