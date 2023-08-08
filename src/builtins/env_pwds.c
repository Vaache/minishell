/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:38:05 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/08 12:21:26 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_init(t_env_list *my_env);

void	pwd_init(t_env_list *my_env)
{
	t_env_list	*tmp;
	char		*str;
	static int	i = 0;

	tmp = my_env;
	str = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			str = ft_strdup(tmp->data);
			if (tmp->flag == 1)
			{
				i = tmp->flag;
				tmp->flag = 2;
			}
			break ;
		}
		tmp = tmp->next;
	}
	tmp = my_env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0 && i == 1)
		{
			free(tmp->line);
			tmp->line = ft_strdup("");
			tmp->line = ft_strjoin(tmp->line, "OLDPWD", 1);
			tmp->line = ft_strjoin(tmp->line, "=", 1);
			i = 0;
			break ;
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0 && i == 0)
		{
			free(tmp->data);
			free(tmp->line);
			tmp->data = ft_strdup(str);
			tmp->line = ft_strdup("");
			tmp->line = ft_strjoin(tmp->line, "OLDPWD", 1);
			tmp->line = ft_strjoin(tmp->line, "=", 1);
			tmp->line = ft_strjoin(tmp->line, tmp->data, 1);
			break ;
		}
		tmp = tmp->next;
		if (tmp == NULL)
		{
			push_back(&my_env, malloc_list("OLDPWD"));
			tmp = my_env;
		}
	}
	free(str);
}
