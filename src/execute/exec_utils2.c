/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:10:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/08 20:31:33 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_main *main, t_env **env);
char	*fill_path_cmd(char *cmd, char **path);
int		andxor(t_tok *stack);

void	find_path(t_main *main, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			if (tmp->flag == 1)
			{
				main->path = NULL;
				return ;
			}
			break ;
		}
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
	while (path && path[i] && cmd[0] != '\0')
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

int	andxor(t_tok *stack)
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
