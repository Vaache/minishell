/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:36:14 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/06 12:27:06 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*malloc_list(char *env);
t_env_list	*push_back(t_env_list **list, t_env_list *new);

t_env_list	*malloc_list(char *env)
{
	t_env_list	*tmp;
	int			i;

	i = 0;
	tmp = (t_env_list *)malloc(sizeof(t_env_list));
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

t_env_list	*push_back(t_env_list **list, t_env_list *new)
{
	t_env_list	*ptr;

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
