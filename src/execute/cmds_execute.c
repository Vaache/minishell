/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:17:41 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 20:13:17 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_main *main, t_pars *pars, t_env *env)
{
	char	*str;
	int		i;
	(void)main;

	i = 0;
	str = NULL;
	if (ft_strcmp(pars->cmd, "env") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_env(str, env);
		return (1);
	}
	else if (ft_strcmp(pars->cmd, "pwd") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_pwd(str);
		return (1);
	}
	else if (ft_strcmp(pars->cmd, "cd") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_cd(str, env);
		return (1);
	}
	else if (ft_strcmp(pars->cmd, "exit") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_exit(str);
		return (1);
	}
	else if (ft_strcmp(pars->cmd, "export") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_export(str, env);
		return (1);
	}
	else if (ft_strcmp(pars->cmd, "unset") == 0)
	{
		str = restore_cmds_line(pars);
		minishell_unset(str, env);
		return (1);
	}
	return (0);
}

int	cmds_execute(t_main *main, t_pars *pars, t_env *env, int status)
{
	(void)status;
	check_builtins(main, pars, env);
	return (0);
}