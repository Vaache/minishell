/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:28:20 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 19:31:21 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_cd(char *str, t_env *my_env);

void	minishell_cd(char *str, t_env *my_env)
{
	char	**arr;
	t_env	*tmp;
	char	buff[1024];

	pwd_init(my_env);
	arr = ft_split(str, ' ');
	if (!arr[1])
	{
		tmp = my_env;
		while (ft_strcmp(tmp->key, "HOME") != 0)
			tmp = tmp->next;
		chdir(tmp->data);
	}
	else if (chdir(arr[1]) != 0)
		ft_printf(1, "cd: no such file or directory: %s\n", arr[1]);
	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->data);
			free(tmp->line);
			getcwd(buff, sizeof(buff));
			tmp->data = ft_strdup(buff);
			tmp->line = ft_strdup("");
			tmp->line = ft_strjoin(tmp->line, "PWD", 1);
			tmp->line = ft_strjoin(tmp->line, "=", 1);
			tmp->line = ft_strjoin(tmp->line, tmp->data, 1);
			break ;
		}
		tmp = tmp->next;
	}
	free_2d(arr, strlen_2d(arr));
}