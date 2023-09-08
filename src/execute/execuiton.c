/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuiton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:11:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/08 15:44:48 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		call_cmds(t_main *main, t_tok *stack, t_env **env);
int		exec_cmds(char *path_cmd, char **cmd_arr, char **env, t_tok *stack);
char	*check_cmd(char *cmd, char **path);
int		exec_cmds2(pid_t pid, t_tok **stack);

int	exec_cmds(char *path_cmd, char **cmd_arr, char **env, t_tok *stack)
{
	pid_t	pid;

	pid = fork();
	run_signals(2);
	if (pid == -1)
	{
		perror("Minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			exit(EXIT_FAILURE);
		if (execve(path_cmd, cmd_arr, env) == -1 && \
			execve(cmd_arr[0], cmd_arr, env) == -1)
		{
			ft_printf(2, "Minishell: %s: is a directory\n", cmd_arr[0]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
		return (exec_cmds2(pid, &stack));
}

int	exec_cmds2(pid_t pid, t_tok **stack)
{
	int	childe_exit;

	childe_exit = 0;
	waitpid(pid, &childe_exit, 0);
	g_exit_status_ = childe_exit % 255;
	if (io_backup_dup2((*stack)->stdin_backup, (*stack)->stdout_backup))
		return (1);
	return (childe_exit / 256);
}

char	*check_cmd(char *cmd, char **path)
{
	char	*path_cmd;

	path_cmd = NULL;
	if (access(cmd, X_OK | F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			ft_printf(2, "Minishell: %s: no such file or directory\n", cmd);
			g_exit_status_ = 127;
			return (NULL);
		}
		path_cmd = fill_path_cmd(cmd, path);
		if (!path_cmd)
		{
			g_exit_status_ = 127;
			ft_printf(2, "Minishell: command not found: %s\n", cmd);
		}
		return (path_cmd);
	}
	return (ft_strdup(cmd));
}

int	call_cmds(t_main *main, t_tok *stack, t_env **env)
{
	char	*cmd_path;
	char	**cmd_arr;
	char	**my_env;
	int		k;

	if (main->flag)
	{
		find_path(main, env);
		main->flag = 0;
	}
	call_expand(stack, *env);
	if (lstsize(stack) == 1 && stack->cmd[0] == '\0')
		return (0);
	cmd_arr = restore_cmd_line(stack, -1);
	my_env = env_2d(env);
	cmd_path = check_cmd(cmd_arr[0], main->path);
	if (!cmd_path)
		return (127 + free_of_n(NULL, cmd_arr, my_env, 2));
	k = exec_cmds(cmd_path, cmd_arr, my_env, stack);
	free_2d(main->path);
	free_of_n(cmd_path, cmd_arr, my_env, 3);
	return (error_code(k));
}
