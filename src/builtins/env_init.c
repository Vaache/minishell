/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:30:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/18 14:34:29 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_init(char **env, t_env *my_env);

t_env	*env_init(char **env, t_env *my_env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		my_env = push_back(&my_env, malloc_list(env[i]));
		i++;
		if (env[i] == NULL)
			my_env = push_back(&my_env, malloc_list("$?=0"));
	}
	return (my_env);
}
