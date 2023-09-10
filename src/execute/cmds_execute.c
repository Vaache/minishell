/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 10:19:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_tok *pars, t_env **env);
int	exec_builtins(t_tok *stack, t_env **env, char **arr);
int	is_builtin(char **arr, t_tok *stack);

int	cmds_execute(t_main *main, t_tok *pars, t_env **env, int status)
{
	status = check_builtins(pars, env);
	if (status == 1 && status != 127)
		status = call_cmds(main, pars, env);
	else if (status == -1)
		return (1);
	else
		if (io_backup_dup2(pars->stdin_backup, pars->stdout_backup))
			return (1);
	main->flag = 1;
	if (g_exit_status_ == -42)
		return (1);
	return (status);
}

int	check_builtins(t_tok *pars, t_env **env)
{
	char	**arr;
	int		status;

	call_expand(pars, *env);
	arr = restore_cmd_line(pars, -1);
	if (!arr || !arr[0])
		return (1);
	status = is_builtin(arr, pars);
	if (!status)
	{
		status = exec_builtins(pars, env, arr);
	}
	free_2d(arr);
	return (status);
}

int	exec_builtins(t_tok *stack, t_env **env, char **arr)
{
	if (ft_strcmp(arr[0], _ENV_) == 0)
	{
		if (arr[1] != NULL)
		{
			ft_printf(2, "%s: %s: No such file or directory\n", arr[0], arr[1]);
			return (127);
		}
		minishell_env(env);
	}
	else if (ft_strcmp(arr[0], _ECHO_) == 0)
		minishell_echo(arr);
	else if (ft_strcmp(arr[0], _PWD_) == 0)
		minishell_pwd(arr[0], env);
	else if (ft_strcmp(arr[0], _CD_) == 0)
		minishell_cd(arr, env);
	else if (ft_strcmp(arr[0], _EXIT_) == 0)
		return (minishell_exit(stack, arr, env, NULL));
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
