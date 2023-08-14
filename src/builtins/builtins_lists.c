/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:36:14 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 12:14:13 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*malloc_list(char *env);
t_env	*push_back(t_env **list, t_env *new);

t_env	*malloc_list(char *env)
{
	t_env	*tmp;
	int			i;

	i = 0;
	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->next = NULL;
	tmp->prev = NULL;
	while (env && env[i] != '\0' && env[i] != '=')
		i++;
	tmp->key = ft_substr(env, 0, (size_t)i);
	tmp->data = ft_substr(env, i + 1, ft_strlen(&env[i + 1]));
	tmp->line = ft_strdup(env);
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
