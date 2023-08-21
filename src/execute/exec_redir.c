/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:41:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/21 19:30:29 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_main *main, t_pars *stack, t_env *env);
int	heredoc(t_main *main, t_pars *stack, t_env *env);
int	input(t_main *main, t_pars *stack, t_env *env);
int	minishell_pipe(t_main *main, t_pars *stack, t_env *env);
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
	int		fd[2];
	int		stdin_backup;
	int		pid;
	int		status;
	t_pars	*tmp;

	stdin_backup = 0;
	status = 0;
	stdin_backup = dup(STDIN_FILENO);
	tmp = stack;
	if (pipe(fd) < 0)
	{
		perror("minishell");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd(stack->right->cmd, fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close (fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			close(fd[0]);
			perror("minishell");
			return (1);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
		{
			while (stack && stack->left && stack->left->left)
				stack = stack->left;
			if (ft_strcmp(stack->left->cmd, "(NULL)"))
				main->exit_status = cmds_execute(main, stack->left, env, 0);
		}
		close (fd[0]);
		if (dup2(stdin_backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (1);
		}
		close (stdin_backup);
	}
	return (0);
}

int	input(t_main *main, t_pars *stack, t_env *env)
{
	int		status;
	int		fd[2];
	int		file_fd;
	int		backup;
	char	*str;
	int		pid;

	backup = dup(STDIN_FILENO);
	if (pipe(fd) < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell");
		close(fd[0]);
		close(fd[1]);
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		file_fd = open(stack->right->cmd, O_RDONLY);
		if (file_fd == -1)
		{
			close (fd[1]);
			perror("Minishell");
			exit (1);
		}
		while (1)
		{
			str = get_next_line(file_fd);
			if (!str)
				break ;
			ft_putstr_fd(str, fd[1]);
		}
		close (fd[1]);
		close (file_fd);
		exit (EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("minishell");
			close (fd[0]);
			return (EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
		while (stack->left->type != WORD)
			stack = stack->left;
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			main->exit_status = cmds_execute(main, stack->left, env, 0);
		close (fd[0]);
		if (dup2(backup, STDIN_FILENO) < 0)
		{
			perror("minishell");
			return (EXIT_FAILURE);
		}
		close (backup);
	}
	return (0);
}

int	exec_iocmd(t_main *main, t_pars *stack, t_env *env)
{
	if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
		return (redir(main, stack, env));
	else if (stack && stack->type == HEREDOC)
		return (heredoc(main, stack, env));
	else if (stack->type == INPUT)
		return (input(main, stack, env));
	return (1);
}
