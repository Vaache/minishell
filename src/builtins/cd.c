/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:20 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/19 17:05:30 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_cd(char **arr, t_env *my_env);

void	minishell_cd(char **arr, t_env *my_env)
{
	t_env	*tmp;
	char	*buff;

	buff = NULL;
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
		ft_printf(1, "Minishell: cd: no such file or directory: %s\n", arr[1]);
	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->data);
			buff = getcwd(buff, sizeof(buff));
			tmp->data = ft_strdup(buff);
			free(buff);
			break ;
		}
		tmp = tmp->next;
	}
}