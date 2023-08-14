/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:26:40 by vhovhann          #+#    #+#             */
/*   Updated: 2023/08/14 12:51:16 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_env(char *str, t_env *env)
{
	t_env	*tmp;
	(void)str;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->flag == 0)
			ft_printf(1, "%s\n", tmp->line);
		tmp = tmp->next;
	}

}