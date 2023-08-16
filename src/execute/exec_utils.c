/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:19:34 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/16 17:41:37 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*restore_cmds_line(t_pars *stack);
void	find_path(t_main *main, t_env *env);
int		check_xandxor(t_pars *stack);

char	*restore_cmds_line(t_pars *stack)
{
	char	*cmd;
	int		mode;
	t_pars	*tmp;

	cmd = NULL;
	tmp = stack;
	while (tmp && tmp->cmd)
	{
		mode = (tmp->flag & (1 << 1)) && 1;
		if (!cmd || (mode == 0 && check_types(tmp->type) == 0))
				cmd = ft_strjoin(cmd, tmp->cmd, 1);
		else
			cmd = strjoin_mode(cmd, tmp->cmd, 0);
		tmp = tmp->next;
	}
	cmd[ft_strlen(cmd)] = '\0';
	return (cmd);
}
void	find_path(t_main *main, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			break ;
		tmp = tmp->next;
	}
	main->path = ft_split(tmp->data, ':');
}

char	*fill_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*cmdpath;

	i = 0;
	cmdpath = NULL;
	while (path && path[i])
	{
		cmdpath = ft_strjoin(path[i], "/", 0);
		cmdpath = ft_strjoin(cmdpath, cmd, 1);
		if (access(cmdpath, X_OK | F_OK) == -1)
			free(cmdpath);
		else
			return (cmdpath);
		i++;
	}
	return (NULL);
}
int	check_xandxor(t_pars *stack)
{
	if (stack->type == XAND && stack->left && stack->left->err_code != 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else if (stack->type == XOR && stack->left && stack->left->err_code == 0)
	{
		stack->err_code = stack->left->err_code;
		return (0);
	}
	else
		return (1);
}