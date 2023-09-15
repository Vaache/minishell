/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:10:54 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/15 21:57:00 by vhovhann         ###   ########.fr       */
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
				main->flag = 1;
			else
				main->flag = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (!main->path)
		main->path = ft_split(tmp->data, ':');
}

char	*fill_path_cmd(char *cmd, char **path)
{
	int		i;
	char	*cmdpath;

	i = 0;
	cmdpath = NULL;
	if (cmd[0] == '\0' && ft_strlen(cmd) == 1)
		return (NULL);
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

int	open_out(t_tok *stack)
{
	int	fd;

	fd = 0;
	if (stack->type == WRITE_APPEND)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_APPEND, 0655);
	else if (stack->type == WRITE_TRUNC)
		fd = open(stack->right->cmd, O_RDWR | O_CREAT | O_TRUNC, 0655);
	if (fd == -1)
		perror("minishell");
	return (fd);
}

int	open_input(t_tok *stack)
{
	int	fd;

	fd = open(stack->right->cmd, O_RDONLY);
	if (fd < 0)
		ft_printf(2, "minishell: %s: No such file or directory\n", \
									stack->right->cmd);
	return (fd);
}
