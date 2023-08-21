/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:19:34 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/21 21:46:59 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**restore_cmd_line(t_pars *stack);
void	find_path(t_main *main, t_env *env);
int		andxor(t_pars *stack);

char	**restore_cmd_line(t_pars *stack)
{
	char		**cmd_matrix;
	int			mode;
	t_pars		*tmp;
	int			i;

	tmp = stack;
	i = 0;
	cmd_matrix = (char **)malloc(sizeof(char *) * (lstsize(tmp) + 1));
	if (!cmd_matrix)
		return (NULL);
	while (i < lstsize(tmp))
		cmd_matrix[i++] = NULL;
	i = -1;
	while (tmp && tmp->cmd)
	{
		mode = ((tmp->flag & (1 << 1)) && 1);
		if (mode == 0 && check_types(tmp->type) == 0)
		{
			if (i < 0)
				i++;
			cmd_matrix[i] = ft_strjoin(cmd_matrix[i], tmp->cmd, 1);
		}
		else
		{
			i++;
			cmd_matrix[i] = ft_strdup(tmp->cmd);
		}
		tmp = tmp->next;
	}
	cmd_matrix[i + 1] = NULL;
	return (cmd_matrix);
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

int	andxor(t_pars *stack)
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
