/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 14:37:16 by vhovhann          #+#    #+#             */
/*   Updated: 2023/09/10 19:56:13 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dollar(int exit_status, t_env **env)
{
	t_env	*tmp;
	char	*status;

	tmp = (*env);
	status = ft_itoa(exit_status);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "$?"))
		{
			free(tmp->data);
			tmp->data = ft_strdup(status);
			break ;
		}
		tmp = tmp->next;
	}
	free(status);
}
