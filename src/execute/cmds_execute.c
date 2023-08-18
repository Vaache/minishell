/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/18 13:16:17 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_main *main, t_pars *pars, t_env *env)
{
	char	*str;
	char	**arr;
	int		i;
	(void)main;

	i = 0;
	str = restore_cmds_line(pars);
	if (str[0] == '\0' || !onlyspace(str))
	{
		free(str);
		return (0);
	}
	arr = ft_split(str, ' ');
	free(str);
	if (ft_strcmp(arr[0], "env") == 0)
	{
		if (arr[1] != NULL)
		{
			ft_printf(2, "env: %s: No such file or directory\n", arr[1]);
			free_2d(arr);
			return (0);
		}
		minishell_env(arr[0], env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "echo") == 0)
	{
		minishell_echo(arr);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "pwd") == 0)
	{
		minishell_pwd(str);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "cd") == 0)
	{
		minishell_cd(arr, env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "exit") == 0)
	{
		minishell_exit(arr);
		// free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "export") == 0)
	{
		minishell_export(arr, env);
		free_2d(arr);
		return (1);
	}
	else if (ft_strcmp(arr[0], "unset") == 0)
	{
		minishell_unset(arr, env);
		free_2d(arr);
		return (1);
	}
	free_2d(arr);
	return (0);
}

int	cmds_execute(t_main *main, t_pars *pars, t_env *env, int status)
{
	if (!check_builtins(main, pars, env))
	{
		pars->err_code = call_cmds(main, pars, env);
		main->exit_status = pars->err_code;
	}
	return (status);
}