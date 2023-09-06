/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/06 18:46:26 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins_2(t_env **env, char **arr);
int	check_builtins(t_tok *pars, t_env **env);

int	check_builtins(t_tok *pars, t_env **env)
{
	char	**arr;

	call_expand(pars, *env);
	arr = restore_cmd_line(pars, -1);
	if (!arr)
		return (0);
	if (!ft_strcmp(arr[0], _ENV_) || !ft_strcmp(arr[0], _ECHO_) || \
			!ft_strcmp(arr[0], _PWD_) || !ft_strcmp(arr[0], _CD_) || \
				!ft_strcmp(arr[0], _EXIT_) || !ft_strcmp(arr[0], _EXPORT_) || \
													!ft_strcmp(arr[0], _UNSET_))
		if (io_dup2(pars->_stdin_, pars->_stdout_))
			return (-1);
	if (check_builtins_2(env, arr))
	{	
		free_2d(arr);
		return (1);
	}
	free_2d(arr);
	return (0);
}

int	check_builtins_2(t_env **env, char **arr)
{
	if (ft_strcmp(arr[0], _ENV_) == 0)
	{
		if (arr[1] != NULL)
			return (0);
		minishell_env(env);
	}
	else if (ft_strcmp(arr[0], _ECHO_) == 0)
		minishell_echo(arr);
	else if (ft_strcmp(arr[0], _PWD_) == 0)
		minishell_pwd(arr[0], env);
	else if (ft_strcmp(arr[0], _CD_) == 0)
		minishell_cd(arr, env);
	else if (ft_strcmp(arr[0], _EXIT_) == 0)
		minishell_exit(arr, env, NULL);
	else if (ft_strcmp(arr[0], _EXPORT_) == 0)
		minishell_export(arr, env);
	else if (ft_strcmp(arr[0], _UNSET_) == 0)
		minishell_unset(arr, env);
	else
		return (0);
	return (1);
}

int	cmds_execute(t_main *main, t_tok *pars, t_env **env, int status)
{
	status = check_builtins(pars, env);
	if (status == 0)
	{
		pars->err_code = call_cmds(main, pars, env);
		status = pars->err_code;
	}
	else if (status == -1)
		return (1);
	else
		if (io_backup_dup2(pars->stdin_backup, pars->stdout_backup))
			return (1);
	main->flag = 1;
	return (0);
}
