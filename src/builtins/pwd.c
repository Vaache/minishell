/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:30:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/19 17:43:33 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_pwd(char *str);
void	pwd_init(t_env *my_env);

void	minishell_pwd(char *str)
{
	char	*buff;
	(void)str;

	buff = getcwd(NULL, 0);
	if (buff != NULL)
		printf("%s\n", buff);
	else
		perror("getcwd");
	free(buff);
}

void	pwd_init(t_env *my_env)
{
	t_env		*tmp;
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
			free(tmp->data);
			tmp->data = ft_strdup("");
			i = 0;
			break ;
		}
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0 && i == 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(str);
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
