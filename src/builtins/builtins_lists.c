/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:36:14 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/20 13:03:00 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*malloc_list(char *env);
t_env	*push_back(t_env **list, t_env *new);

t_env	*malloc_list(char *env)
{
	t_env	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->next = NULL;
	tmp->prev = NULL;
	while (env && env[i] != '\0' && env[i] != '=')
		i++;
	tmp->key = ft_substr(env, 0, (size_t)i);
	tmp->data = ft_substr(env, i + 1, ft_strlen(&env[i + 1]));
	if (!ft_strcmp(tmp->key, "SHLVL") && \
		(!ft_strcmp(tmp->data, "1") || !ft_strcmp(tmp->data, "2")))
	{
		str = ft_itoa(ft_atoi(tmp->data) + 1);
		free(tmp->data);
		tmp->data = ft_strdup(str);
		free(str);
	}
	if (!ft_strcmp(tmp->key, "$?"))
		tmp->flag = 1;
	else
		tmp->flag = 0;
	return (tmp);
}

t_env	*push_back(t_env **list, t_env *new)
{
	t_env	*ptr;

	ptr = *list;
	if (ptr == NULL)
		list = &new;
	else
	{	
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		new->prev = ptr;
	}
	return (*list);
}

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		(lst) = (lst)->next;
	}
	return (i);
}

char	**env_2d(t_env *env)
{
	char	**my_env;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	my_env = (char **)malloc(sizeof(char *) * (env_lstsize(tmp) + 1));
	if (!my_env)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		my_env[i] = ft_strdup(tmp->key);
		my_env[i] = ft_strjoin(my_env[i], "=", 1);
		my_env[i] = ft_strjoin(my_env[i], tmp->data, 1);
		i++;
		tmp = tmp->next;
	}
	my_env[i] = NULL;
	return (my_env);
}
