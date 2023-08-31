/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:41:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 22:43:27 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_main *main, t_pars *stack, t_env **env);
int	input(t_main *main, t_pars *stack, t_env **env);
int	heredoc(t_main *main, t_pars *stack, t_env **env);
int	exec_iocmd(t_main *main, t_pars *stack, t_env **env);

int	redir(t_main *main, t_pars *stack, t_env **env)
{
	int		exit_status;
	int		fd;
	t_pars	*tmp;

	exit_status = 0;
	fd = -42;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_APPEND, 0655);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd == -1)
	{
		perror("Minishell");
		return (1);
	}
	if (--main->redir > 0)
		;
	if (main->redir == 0)
		stack->last_red = 1;
	if (stack->last_red != 1)
		return (1);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	if (ft_strcmp(tmp->left->cmd, "(NULL)") && !(tmp->flag & (1 << 7)))
	{
		tmp->left->stdout_backup = main->stdout_backup;
		tmp->left->_stdout_ = fd;
		exit_status = cmds_execute(main, tmp->left, env, 0);
	}
	return (exit_status);
}

int heredoc(t_main *main, t_pars *stack, t_env **env)
{
	char	*res;
	int		fd;
	t_pars	*tmp;

	if (--main->hdoc > 0)
		;
	if (main->hdoc == 0)
		stack->last_hdoc = 1;
	res = NULL;
	fd = -42;
	if (stack->last_hdoc != 1)
	{
		res = handle_heredoc_input(stack->right->cmd);
		free(res);
		return (0);
	}
	res = handle_heredoc_input(stack->right->cmd);
	if (!res)
		return (1);
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	write(fd, res, ft_strlen(res));
	free(res);
	close(fd);
	fd = open(".heredoc", O_RDWR, 0655);
	if (fd < 0)
	{
		perror("minishell");
		return (EXIT_FAILURE);
	}
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	if (main->redir != 0)
	{
		tmp->left->stdin_backup = main->stdin_backup;
		tmp->left->_stdin_ = fd;
		return (1);
	}
	if (ft_strcmp(tmp->left->cmd, "(NULL)"))
	{
		tmp->left->stdin_backup = main->stdin_backup;
		tmp->left->_stdin_ = fd;
		main->exit_status = check_astree(main, tmp->left, env);
	}
	
	return (0);
}

int	input(t_main *main, t_pars *stack, t_env **env)
{
	static int	i = 0;
	int			fd;
	t_pars		*tmp;

	if (--main->input > 0)
		;
	if (main->input == 0)
		stack->last_input = 1;
	fd = open(stack->right->cmd, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		i = 1;
		return(EXIT_FAILURE);
	}
	if (i == 1)
		return(1);
	tmp = stack;
	while (tmp->left->type != WORD)
		tmp = tmp->left;
	if (stack->last_input != 1)
		return (0);
	if (main->redir != 0)
	{
		tmp->left->stdin_backup = main->stdin_backup;
		tmp->left->_stdin_ = fd;
		return (1);
	}
	tmp->left->stdin_backup = main->stdin_backup;
	tmp->left->_stdin_ = fd;
	main->exit_status = cmds_execute(main, tmp->left, env, 0);
	i = 0;
	return (0);
}

int	exec_iocmd(t_main *main, t_pars *stack, t_env **env)
{
	if (stack && stack->type == HEREDOC)
		return (heredoc(main, stack, env));
	else if (stack->type == WRITE_APPEND || stack->type == WRITE_TRUNC)
		return (redir(main, stack, env));
	else if (stack->type == INPUT)
		return (input(main, stack, env));
	return (1);
}
	