/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:20 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/25 17:36:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_cd(char **arr, t_env *my_env);
void	minishell_cd_helper(char *str, t_env **my_env);

void	minishell_cd(char **arr, t_env *my_env)
{
	t_env	*tmp;
	char	*str;

	str = NULL;
	pwd_init(my_env);
	if (!arr)
		return ;
	if (!arr[1])
	{
		tmp = my_env;
		while (ft_strcmp(tmp->key, "HOME") != 0 && tmp->flag != 1)
			tmp = tmp->next;
		chdir(tmp->data);
	}
	else if (chdir(arr[1]) != 0)
		ft_printf(2, "Minishell: cd: no such file or directory: %s\n", arr[1]);
	minishell_cd_helper(str, &my_env);
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
				ft_printf(2, "cd: error retrieving current directory: %s\n", \
					"getcwd: cannot access parent directories: No such file or directory");
			tmp->data = ft_strdup(str);
			if (str)
			{
				free(tmp->data);
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
