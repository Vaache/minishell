/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuiton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:11:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 17:50:13 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_astree(t_main *main, t_pars *stack, t_env *env);
int		call_cmds(t_main *main, t_pars *stack, t_env *env);
int	exec_cmds(char *path_cmd, char **cmd_arr, char **env);
char	*check_cmd(char *cmd, char **path);

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
	if (stack->right != NULL && check_xandxor(stack) && !(stack->right->flag & (1 << 3)))
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

int	exec_cmds(char *path_cmd, char **cmd_arr, char **env)
{
	pid_t	pid;
	int		childeExit;
	
	childeExit = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Minishell");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path_cmd, cmd_arr, env) == -1 && \
			execve(cmd_arr[0], cmd_arr, env) == -1)
		{
			perror("Minishell");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &childeExit, 0);
		return (childeExit / 256);
	}
}

char	*check_cmd(char *cmd, char **path)
{
	char	*path_cmd;

	path_cmd = NULL;
	// if (!ft_strcmp(cmd, "./minishell") || !ft_strcmp(cmd, "minishell"))
	// 	return (ft_strdup(cmd));
	if (access(cmd, X_OK | F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			ft_printf(2, "Minishell: no such file or directory: %s\n", cmd);
			return (NULL);
		}
		path_cmd = fill_path_cmd(cmd, path);
		if (!path_cmd)
			ft_printf(2, "Minishell: command not found: %s\n", cmd);
		return (path_cmd);
	}
	return (ft_strdup(cmd));
}

int	call_cmds(t_main *main, t_pars *stack, t_env *env)
{
	char	*cmd;
	char	*cmd_path;
	char	**cmd_arr;
	char	**my_env;
	int		k;

	if (!main->path)
		find_path(main, env);
	my_env = env_2d(env);
	cmd = restore_cmds_line(stack);
	if (!cmd)
		return (1);
 	cmd_arr = ft_split(cmd, ' ');
	if (!cmd_arr)
	{
		free(cmd);
		return (2);
	}
	cmd_path = check_cmd(cmd_arr[0], main->path);
	if (!cmd_path)
	{
		free(cmd);
		free_2d(cmd_arr);
		return (127);
	}
	k = exec_cmds(cmd_path, cmd_arr, my_env);
	free(cmd);
	free(cmd_path);
	free_2d(cmd_arr);
	free_2d(my_env);
	return (error_code(k));
}
