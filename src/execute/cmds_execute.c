/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/16 16:44:41 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_tok *pars, t_env **env);
int	exec_builtins(t_tok *stack, t_env **env, char **arr);
int	is_builtin(char **arr, t_tok *stack);

int	cmds_execute(t_main *main, t_tok *pars, t_env **env, int status)
{
	status = check_builtins(pars, env);
	if (status == 1)
		status = call_cmds(main, pars, env);
	else
		if (io_backup_dup2(pars->stdin_backup, pars->stdout_backup))
			return (1);
	if (g_exit_status_ == -42)
		return (1);
	if (g_exit_status_ == -100)
		return (pars->err_code);
	return (status);
}

int	check_builtins(t_tok *pars, t_env **env)
{
	char	**arr;
	char	*str;
	int		status;

	status = 0;
	str = ft_strdup(pars->cmd);
	if (call_expand(pars, *env) && pars->cmd[0] == '\0' && lstsize(pars) == 1)
	{
		free (pars->cmd);
		pars->cmd = str;
		return (1);
	}
	free(str);
	arr = restore_cmd_line(pars, -1);
	if (!arr || !arr[0])
		return (1);
	status = is_builtin(arr, pars);
	if (!status)
		status = exec_builtins(pars, env, arr);
	free_2d(arr);
	return (status);
}

int	exec_builtins(t_tok *stack, t_env **env, char **arr)
{
	if (ft_strcmp(arr[0], _ENV_) == 0)
	{
		if (arr[1] != NULL)
			return (127 + (ft_printf(2, "%s: %s: %s\n", \
					arr[0], arr[1], "No such file or directory") * 0));
		minishell_env(env);
	}
	else if (ft_strcmp(arr[0], _ECHO_) == 0)
		minishell_echo(arr);
	else if (ft_strcmp(arr[0], _PWD_) == 0)
		minishell_pwd(arr[0], env);
	else if (ft_strcmp(arr[0], _CD_) == 0)
		minishell_cd(arr, env);
	else if (ft_strcmp(arr[0], _EXIT_) == 0)
	{
		stack->err_code = minishell_exit(stack, arr, env, NULL);
		g_exit_status_ = -100;
	}
	else if (ft_strcmp(arr[0], _EXPORT_) == 0)
		minishell_export(arr, env);
	else if (ft_strcmp(arr[0], _UNSET_) == 0)
		minishell_unset(arr, env);
	else
		return (1);
	return (0);
}

int	is_builtin(char **arr, t_tok *stack)
{
	if (!ft_strcmp(arr[0], _ENV_) || !ft_strcmp(arr[0], _ECHO_) || \
			!ft_strcmp(arr[0], _PWD_) || !ft_strcmp(arr[0], _CD_) || \
			!ft_strcmp(arr[0], _EXIT_) || !ft_strcmp(arr[0], _EXPORT_) || \
			!ft_strcmp(arr[0], _UNSET_))
	{
		if (io_dup2(stack->_stdin_, stack->_stdout_))
			return (-1);
		else
			return (0);
	}
	return (1);
}
