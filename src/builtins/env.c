/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:26:40 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/27 22:50:23 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_env(t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp != NULL)
	{
		if (tmp->flag == 0)
			ft_printf(1, "%s=%s\n", tmp->key, tmp->data);
		tmp = tmp->next;
	}
}
