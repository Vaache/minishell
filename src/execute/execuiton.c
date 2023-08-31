/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execuiton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:11:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/31 17:42:53 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_astree(t_main *main, t_pars *stack, t_env **env);
int		call_cmds(t_main *main, t_pars *stack, t_env **env);
int		exec_cmds(char *path_cmd, char **cmd_arr, char **env, int stdin_backup);
char	*check_cmd(char *cmd, char **path);

int	check_astree(t_main *main, t_pars *stack, t_env **env)
{
	int		status;
	// pid_t	pid;

	status = 0;
	if (!stack)
	{
		main->exit_status = 258;
		return (main->exit_status);
	}
	if (stack->left == NULL && stack->right == NULL)
	{
		main->exit_status = cmds_execute(main, stack, env, status);
		handle_dollar(main->exit_status, env);
		return (main->exit_status);
	}
	if (stack->left && stack->right && (check_types(stack->type) == 2))
	{
		if (stack->left->left)
			check_astree(main, stack->left, env);
		main->exit_status = exec_iocmd(main, stack, env);
	}
	else if (stack->left && stack->right && stack->type == PIPE && (stack->left->type != HEREDOC || stack->right->type != HEREDOC))
		stack->err_code = pipe_prepair(main, stack, env);
	if (stack->left != NULL && !(stack->left->flag & _REDIR_) && !(stack->right->flag & _PIPE_))
	{
		// if (stack->left->subshell_code)
		// {
		// 	pid = fork();
		// 	if (pid == -1)
		// 		return (127);
		// 	else if (pid == 0)
		// 	{
		// 		stack->err_code = check_astree(main, stack->left, env);
		// 		exit (stack->err_code);
		// 	}
		// 	else
		// 	{
		// 		if (wait(&status) < 0)
		// 		{
		// 			perror("wait");
		// 				return (1);
		// 		}
		// 		return (status);
		// 	}
		// }
		// else
			stack->err_code = check_astree(main, stack->left, env);
	}
	if (stack->right != NULL && andxor(stack) && !(stack->right->flag & _REDIR_) && !(stack->right->flag & _PIPE_))
	{
		// if (stack->right->subshell_code)
		// {
		// 	pid = fork();
		// 	if (pid == -1)
		// 		return (127);
		// 	else if (pid == 0)
		// 	{
		// 		stack->err_code = check_astree(main, stack->right, env);
		// 		exit(stack->err_code);
		// 	}
		// 	else
		// 		wait(NULL);
		// 	return (1);
		// }
		// else
			stack->err_code = check_astree(main, stack->right, env);
	}
	return (0);
}

int	exec_cmds(char *path_cmd, char **cmd_arr, char **env, int stdin_backup)
{
	pid_t	pid;
	int		childe_exit;

	childe_exit = 0;
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
		waitpid(pid, &childe_exit, 0);
		if (stdin_backup > 0)
		{
			if (dup2(stdin_backup, STDIN_FILENO) < 0)
			{
				perror("minishell");
				unlink(".heredoc");
				return (EXIT_FAILURE + close(stdin_backup));
			}
			close(stdin_backup);
		}
		return (childe_exit / 256);
	}
}

char	*check_cmd(char *cmd, char **path)
{
	char	*path_cmd;

	path_cmd = NULL;
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

int	call_cmds(t_main *main, t_pars *stack, t_env **env)
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
	cmd_arr = restore_cmd_line(stack, -1);
	my_env = env_2d(env);
	if (!cmd_arr)
		return (2 + free_2d(my_env));
	cmd_path = check_cmd(cmd_arr[0], main->path);
	if (!cmd_path)
		return (127 + free_of_n(NULL, cmd_arr, my_env, 2));
	k = exec_cmds(cmd_path, cmd_arr, my_env, main->stdin_backup);
	free_of_n(cmd_path, cmd_arr, my_env, 3);
	return (error_code(k));
}
