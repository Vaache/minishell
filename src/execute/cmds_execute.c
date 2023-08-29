/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/28 14:01:03 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_main *main, t_pars *pars, t_env **env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = restore_cmd_line(pars, -1);
	if (!arr)
		return (0);
	if (ft_strcmp(arr[0], _ENV_) == 0)
	{
		if (arr[1] != NULL)
		{
			free_2d(arr);
			return (0);
		}
		minishell_env(env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], _ECHO_) == 0)
	{
		minishell_echo(arr);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], _PWD_) == 0)
	{
		minishell_pwd(arr[0], env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], _CD_) == 0)
	{
		minishell_cd(arr, env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], _EXIT_) == 0)
	{
		minishell_exit(arr, env);
		return (1);
	}
	else if (ft_strcmp(arr[0], _EXPORT_) == 0)
	{
		minishell_export(arr, env);
		main->flag = 1;
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], _UNSET_) == 0)
	{
		minishell_unset(arr, env);
		main->flag = 1;
		free_2d(arr);
		return (1);
	}
	free_2d(arr);
	return (0);
}

int	cmds_execute(t_main *main, t_pars *pars, t_env **env, int status)
{
	if (!check_builtins(main, pars, env))
	{
		pars->err_code = call_cmds(main, pars, env);
		status = pars->err_code;
	}
	return (status);
}
