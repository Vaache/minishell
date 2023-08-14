/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:30:27 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 12:14:13 by vhovhann         ###   ########.fr       */
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
	}
	return (my_env);
}
