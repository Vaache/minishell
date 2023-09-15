/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:20 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/14 17:18:55 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_cd(char **arr, t_env **my_env);
int		check_home(t_env **env);
void	minishell_cd_helper(char *str, t_env **my_env);

void	minishell_cd(char **arr, t_env **my_env)
{
	char	*str;

	str = NULL;
	pwd_init(my_env);
	if (!arr)
		return ;
	if (!arr[1])
	{
		if (check_home(my_env))
			return ;
	}
	else if (chdir(arr[1]) != 0)
	{
		ft_printf(2, "Minishell: cd: no such file or directory: %s\n", arr[1]);
		g_exit_status_ = 1;
		return ;
	}
	minishell_cd_helper(str, my_env);
}

int	check_home(t_env **env)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	tmp = (*env);
	while (ft_strcmp(tmp->key, "HOME"))
		tmp = tmp->next;
	if (!ft_strcmp(tmp->key, "HOME") && tmp->flag == 1)
	{
		ft_printf(2, "Minishell: cd: HOME not set\n");
		g_exit_status_ = -42;
		return (1);
	}
	chdir(tmp->data);
	str = getcwd(NULL, 0);
	free(tmp->data);
	tmp->data = ft_strdup(str);
	free(str);
	return (0);
}

void	minishell_cd_helper(char *str, t_env **my_env)
{
	t_env	*tmp;

	tmp = (*my_env);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->pwd);
			str = getcwd(NULL, 0);
			if (str == NULL)
				builtins_error("cd", NULL);
			else
			{
				free(tmp->data);
				tmp->data = ft_strdup(str);
				tmp->pwd = ft_strdup(str);
			}
			if (!str)
				tmp->pwd = ft_strjoin(tmp->pwd, "/..", -1);
			free(str);
			break ;
		}
		tmp = tmp->next;
	}
}
