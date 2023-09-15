/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuiton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:11:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/15 17:01:59 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		call_cmds(t_main *main, t_tok *stack, t_env **env);
int		exec_cmds(char *path_cmd, char **cmd_arr, char **env, t_tok *stack);
char	*check_cmd(t_main *main, t_tok *stack, char *cmd, char **path);

void static	exec_error(char *cmd, int err_num, t_tok *stack)
{
	if (err_num == 13)
	{
		ft_printf(2, "minishell: %s: is a directory\n", cmd);
		stack->err_code = 125;
	}
	else
		ft_printf(2, "minishell: %s: Permission denied\n", cmd);
}

int	exec_cmds(char *path_cmd, char **cmd_arr, char **env, t_tok *stack)
{
	pid_t	pid;
	int		child_exit;

	child_exit = 0;
	pid = fork();
	run_signals(2);
	if (pid == -1)
	{
		perror("minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			exit (EXIT_FAILURE);
		if (execve(path_cmd, cmd_arr, env) == -1)
		{
			exec_error(path_cmd, errno, stack);
			exit(EXIT_FAILURE + stack->err_code);
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &child_exit, 0);
	return (child_exit / 256);
}

char	*check_cmd(t_main *main, t_tok *stack, char *cmd, char **path)
{
	char	*cmd_path;

	if (access(cmd, X_OK | F_OK) == -1 && ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			ft_printf(2, "Minishell: %s: No such file or directory\n", cmd);
		else
			ft_printf(2, "Minishell: %s: Permission denied\n", cmd);
		stack->err_code = -1;
		return (NULL);
	}
	else if (access(cmd, X_OK) != -1 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	cmd_path = fill_path_cmd(cmd, path);
	if (!cmd_path)
	{
		ft_printf(2, "Minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	main->flag++;
	return (cmd_path);
}

int static	destroy_unsetcase(char *path, char **arr, char **env, t_tok *s)
{
	ft_printf(2, "minishell: %s: No such file or directory\n", s->cmd);
	free_of_n(path, arr, env, 3);
	return (127);
}

int	call_cmds(t_main *main, t_tok *stack, t_env **env)
{
	char	*cmd_path;
	char	**cmd_arr;
	char	**my_env;
	int		k;

	if (main->flag)
		find_path(main, env);
	if (call_expand(stack, *env) && stack->cmd[0] == '\0' && \
			lstsize(stack) == 1)
		return (0);
	cmd_arr = restore_cmd_line(stack, -1);
	if (!cmd_arr || !cmd_arr[0])
		return (0);
	my_env = env_2d(env);
	cmd_path = check_cmd(main, stack, cmd_arr[0], main->path);
	if (main->flag == 2)
		return (destroy_unsetcase(cmd_path, cmd_arr, my_env, stack));
	if (!cmd_path && stack->err_code == -1)
		return (126 + free_of_n(NULL, cmd_arr, my_env, 2));
	if (!cmd_path)
		return (127 + free_of_n(NULL, cmd_arr, my_env, 2));
	k = exec_cmds(cmd_path, cmd_arr, my_env, stack);
	free_of_n(cmd_path, cmd_arr, my_env, 3);
	return (error_code(k));
}
