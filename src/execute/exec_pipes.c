/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:05:48 by vhovhann          #+#    #+#             */
/*   Updated: 2023/12/04 18:26:44 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_prepair(t_shell *main, t_tok *pars, t_env **env);

static pid_t	child_left(t_shell *main, t_tok *pars, t_env **env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[1], STDOUT_FILENO) < 0)
			return (-1);
		close(pipes[0]);
		close(pipes[1]);
		status = check_astree(main, pars, *env);
		exit (status);
	}
	return (pid);
}

static pid_t	child_right(t_shell *main, t_tok *pars, t_env **env, int *pipes)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipes[0], STDIN_FILENO) < 0)
			return (-1);
		close(pipes[0]);
		close(pipes[1]);
		status = check_astree(main, pars, *env);
		exit (status);
	}
	return (pid);
}

int	pipe_prepair(t_shell *main, t_tok *pars, t_env **env)
{
	pid_t	pid_right;
	pid_t	pid_left;
	int		pipes[2];
	int		status;

	config_right_dups(pars);
	pars->left->flag |= _PIPE_;
	pars->right->flag |= _PIPE_;
	if (pipe(pipes) == -1)
	{
		pars->err_code = 1;
		perror("minishell");
		return (1);
	}
	pid_left = child_left(main, pars->left, env, pipes);
	if (pid_left < 0)
		return (1);
	pid_right = child_right(main, pars->right, env, pipes);
	if (pid_right < 0)
		return (1);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (status / 256);
}
